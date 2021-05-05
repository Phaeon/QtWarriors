#include "controller.hpp"

/**
 * @brief Controller::Controller : Instancie un controller
 * Affiche la vue de démarrage ' _ViewStart '
 */
Controller::Controller() : _Start("Team Guest", Difficulty::Medium), _Choose(),
  _ViewStart(new ViewStart(this)), _ViewChoose(nullptr), _ViewGame(nullptr), _GameManagment(new GameManagment())
{
  _ViewStart->show();
  _ViewStart->adjustSize();

  QScreen *screen = QGuiApplication::primaryScreen();
  _ViewStart->move(screen->geometry().center() - _ViewStart->rect().center());

  connect(_ViewStart, &ViewStart::UpdateUserName, this, &Controller::setUserName);
  connect(_ViewStart, &ViewStart::UpdateDifficulty, this, &Controller::setDifficulty);
  connect(_ViewStart, &ViewStart::Play, this, &Controller::Play);
}

/**
 * @brief Controller::Play : Instancie la vue _ViewChoose et l'affiche
 */
void Controller::Play()
{
  QScreen *screen = QGuiApplication::primaryScreen();
  _ViewStart->close();

  _ViewChoose = new ViewChoose(this, _Start, _Choose, _GameManagment->getPlayer());
  _ViewChoose->move(screen->geometry().center() - _ViewChoose->rect().center());

  connect(_ViewChoose, &ViewChoose::UpdateListPionsGame, this->_GameManagment, &GameManagment::addListPionGame);
  connect(_ViewChoose, &ViewChoose::UpdateListPionsGame, this, &Controller::UpdateGame);
  connect(_ViewChoose, &ViewChoose::UpdateListPionsGameDel, _GameManagment, &GameManagment::removeListPionGame);
  connect(_ViewChoose, &ViewChoose::UpdateListPionsGameDel, this, &Controller::UpdateGame);
  connect(_ViewChoose, &ViewChoose::rejected, this, &Controller::PlayCanceled);
  connect(_ViewChoose, &ViewChoose::accepted, this, &Controller::LoadGame);

  _ViewChoose->exec();
}

/**
 * @brief Controller::UpdateGame : Modifie l'attribut _Player de l'objet _ViewChoose
 */
void Controller::UpdateGame()
{
  _ViewChoose->setPlayer(this->_GameManagment->getPlayer());
}

/**
 * @brief Controller::PlayCanceled : Affiche la vue de démarrage _ViewStart
 */
void Controller::PlayCanceled()
{
  QScreen *screen = QGuiApplication::primaryScreen();
  this->_GameManagment->ViewGameRejected();

  this->_ViewStart = new ViewStart(this);
  _ViewStart->show();
  _ViewStart->adjustSize();
  _ViewStart->move(screen->geometry().center() - _ViewStart->rect().center());

  connect(_ViewStart, &ViewStart::UpdateUserName, this, &Controller::setUserName);
  connect(_ViewStart, &ViewStart::UpdateDifficulty, this, &Controller::setDifficulty);
  connect(_ViewStart, &ViewStart::Play, this, &Controller::Play);
}

/**
 * @brief Controller::LoadGame : Instancie la vue _ViewGame et l'affiche
 */
void Controller::LoadGame()
{
  _ViewGame = new ViewGame(this, _GameManagment->getPlayer(), _GameManagment->getPlayerEnemy(), _GameManagment->getGame());
  connect(_ViewGame, &ViewGame::rejected, this, &Controller::PlayCanceled);
  connect(_ViewGame, &ViewGame::UpdatePositionPawn, _GameManagment, &GameManagment::UpdateBoard);

  _ViewGame->exec();
}

/**
 * @brief Controller::setUserName : Met à jours l'attribut _Name de l'objet _Start
 * @param name : Nom du joueur
 */
void Controller::setUserName(const QString &name)
{
  _Start.setName(name);
}

/**
 * @brief Controller::setDifficulty : Met à jours l'attribut _Difficulty de l'objet _Start
 * @param difficulty : Difficulté de la partie
 */
void Controller::setDifficulty(Difficulty difficulty)
{
  _Start.setDifficulty(difficulty);
}

/**
 * @brief Controller::getStart
 * @return l'attribut _Start
 */
Start Controller::getStart() const
{
  return this->_Start;
}

/**
 * @brief Controller::getChoose
 * @return l'attribut _Choose
 */
Choose Controller::getChoose() const
{
  return this->_Choose;
}

/**
 * @brief Controller::getGameManagement
 * @return l'attribut _GameManagment
 */
GameManagment *Controller::getGameManagement() const
{
  return this->_GameManagment;
}

/**
 * @brief Controller::~Controller : Destructeur
 */
Controller::~Controller()
{
  delete _GameManagment;
  delete _ViewStart;
  delete _ViewChoose;
  delete _ViewGame;
}



