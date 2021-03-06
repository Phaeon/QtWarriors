#include "controller.hpp"

/**
 * @brief Controller::Controller : Instancie un controller
 * Affiche la vue de démarrage ' _ViewStart '
 */
Controller::Controller()
    : _start("Team Guest", Difficulty::Medium),
      _choose(),
      _viewStart(new ViewStart(this)),
      _viewChoose(nullptr),
      _viewGame(nullptr),
      _endGameView(nullptr),
      _gameManagment(new GameManagment())
{

    _viewStart->show();
    _viewStart->adjustSize();

    QScreen *screen = QGuiApplication::primaryScreen();
    _viewStart->move(screen->geometry().center() - _viewStart->rect().center());

    connect(_viewStart, &ViewStart::updateUserName, this, &Controller::setUserName);
    connect(_viewStart, &ViewStart::updateDifficulty, this, &Controller::setDifficulty);
    connect(_viewStart, &ViewStart::play, this, &Controller::play);
}

/**
 * @brief Controller::Play : Instancie la vue _ViewChoose et l'affiche
 */
void Controller::play()
{
    QScreen *screen = QGuiApplication::primaryScreen();

    _viewStart->close();

    _viewChoose = new ViewChoose(this, _start, _choose, _gameManagment->getPlayer());
    _viewChoose->move(screen->geometry().center() - _viewChoose->rect().center());

    connect(_viewChoose, &ViewChoose::updatePawns, this->_gameManagment, &GameManagment::addPawn);
    connect(_viewChoose, &ViewChoose::updatePawns, this, &Controller::updateGame);
    connect(_viewChoose, &ViewChoose::updateDeletedPawns, _gameManagment, &GameManagment::removePawn);
    _gameManagment->setDifficulty(_start.getDifficulty());
    connect(_viewChoose, &ViewChoose::updateDeletedPawns, this, &Controller::updateGame);
    connect(_viewChoose, &ViewChoose::rejected, this, &Controller::playCanceled);
    connect(_viewChoose, &ViewChoose::accepted, this, &Controller::loadGame);

    _viewChoose->exec();

}

/**
 * @brief Controller::UpdateGame : Modifie l'attribut _Player de l'objet _ViewChoose
 */
void Controller::updateGame()
{
    _viewChoose->setPlayer(this->_gameManagment->getPlayer());
}

/**
 * @brief Controller::PlayCanceled : Affiche la vue de démarrage _ViewStart
 */
void Controller::playCanceled()
{
    QScreen * screen = QGuiApplication::primaryScreen();

    delete _gameManagment;

    _gameManagment = new GameManagment();

    this->_viewStart = new ViewStart(this);
    _viewStart->show();
    _viewStart->adjustSize();
    _viewStart->move(screen->geometry().center() - _viewStart->rect().center());

    connect(_viewStart, &ViewStart::updateUserName, this, &Controller::setUserName);
    connect(_viewStart, &ViewStart::updateDifficulty, this, &Controller::setDifficulty);
    connect(_viewStart, &ViewStart::play, this, &Controller::play);

}

/**
 * @brief Controller::LoadGame : Instancie la vue _viewGame et l'affiche
 */
void Controller::loadGame()
{
    _viewGame = new ViewGame(this, _gameManagment->getPlayer(), _gameManagment->getEnemy(), _gameManagment->getGame());

    connect(_viewGame, &ViewGame::updatePositionPawn, _gameManagment, &GameManagment::updateBoard);
    connect(_viewGame, &ViewGame::playerHasPlayed, this, &Controller::treatmentOfGame);

    connect(_gameManagment, &GameManagment::endGame, this, &Controller::treatmentOfEndGame);

    _viewGame->exec();
}

/**
 * @brief Controller::treatmentOfGame : Traite un tour de jeu
 */
void Controller::treatmentOfGame()
{
    _viewGame->deleteTimer();
    _gameManagment->endOfTreatment();
}

/**
 * @brief Controller::treatmentOfEndGame : Traite la fin d'une partie
 * @param val
 */
void Controller::treatmentOfEndGame(STATE_GAME val)
{
    this->_viewGame->close();

    int nbMonster = _gameManagment->getPlayer()->getPawns().count();
    int nbTour = _gameManagment->getTours();

    QString end = QDateTime().currentDateTime().toString("hh:mm:ss AP dd/MM/yyyy");
    QString timeDiff= QString("%1").arg(QDateTime().fromString(_gameManagment->getTime() ,"hh:mm:ss AP dd/MM/yyyy").secsTo(QDateTime().fromString(end ,"hh:mm:ss AP dd/MM/yyyy")));

    _endGameView = new EndGameView(nbMonster, nbTour, timeDiff, val, this->_start.getName());

    int res = _endGameView->exec();

    if(res == QDialog::Accepted)
        playCanceled();

}

/**
 * @brief Controller::setUserName : Met à jours l'attribut _Name de l'objet _Start
 * @param name : Nom du joueur
 */
void Controller::setUserName(const QString &name)
{
    _start.setName(name);
}

/**
 * @brief Controller::setDifficulty : Met à jours l'attribut _Difficulty de l'objet _Start
 * @param difficulty : Difficulté de la partie
 */
void Controller::setDifficulty(Difficulty difficulty)
{
    _start.setDifficulty(difficulty);
}

/**
 * @brief Controller::getStart
 * @return l'attribut _Start
 */
Start Controller::getStart() const
{
    return this->_start;
}

/**
 * @brief Controller::getChoose
 * @return l'attribut _Choose
 */
Choose Controller::getChoose() const
{
    return this->_choose;
}

/**
 * @brief Controller::getGameManagement
 * @return l'attribut _GameManagment
 */
GameManagment * Controller::getGameManagement() const
{
    return this->_gameManagment;
}

/**
 * @brief Controller::~Controller : Destructeur
 */
Controller::~Controller()
{
    delete _gameManagment;
    delete _viewChoose;
    delete _viewGame;
    delete _endGameView;
}



