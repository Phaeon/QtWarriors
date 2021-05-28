#include "startView.hpp"
#include "ui_viewstart.h"

/**
 * @brief ViewStart::ViewStart : Instencie une vue ViewStart, qui affiche la vue permettant de choisir le nom du joueur ainsi qu'une difficulté
 * @param controller : Objet Controller
 * @param parent : Objet QWidget
 */
ViewStart::ViewStart(Controller *controller, QWidget *parent)
    : QMainWindow(parent),
      View(controller),
      ui(new Ui::ViewStart)
{

    ui->setupUi(this);

    setFixedSize(450, 300);

    setWindowFlags(Qt::CustomizeWindowHint);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);

    //créer les actions
    createActions();
    //créer un menu
    createMenu();

    ui->ExitButton->setStyleSheet("background-color: #D30014;");
    ui->PlayButton->setStyleSheet("background-color: #4CD80F;");

    connect(ui->ExitButton, &QPushButton::clicked, this, &QApplication::quit);
}

/**
 * @brief ViewStart::createMenu : Créer un menu d'aide
 */
void ViewStart::createMenu()
{
    QMenu *AboutMenu = menuBar()->addMenu(QIcon::fromTheme("help-contents"), tr(""));

    AboutMenu->setFont(QFont("Bradley Hand ITC", 12));
    AboutMenu->addAction(_aboutAction);
    AboutMenu->addAction(_helpAction);
    AboutMenu->setStyleSheet("background-color: #ADB4B5;");

    ui->menubar->addMenu(AboutMenu);
    ui->menubar->setLayoutDirection(Qt::RightToLeft);
    ui->menubar->setStyleSheet("background-color: #2c91c8;");
    ui->menubar->setFont(QFont("Bradley Hand ITC", 12));

}

/**
 * @brief ViewStart::createActions : Créer deux actions
 */
void ViewStart::createActions()
{
    _aboutAction = new QAction(tr("About"), this);
    _aboutAction->setStatusTip(tr("About game"));
    _aboutAction->setIcon(QIcon::fromTheme("help-about"));
    _aboutAction->setFont(QFont("Bradley Hand ITC", 12));

    connect(_aboutAction, &QAction::triggered, this, &ViewStart::about);

    _helpAction = new QAction(tr("Help"), this);
    _helpAction->setStatusTip(tr("Help"));
    _helpAction->setIcon(QIcon::fromTheme("help-about"));
    _helpAction->setFont(QFont("Bradley Hand ITC", 12));

    connect(_helpAction, &QAction::triggered, this, &ViewStart::help);

}

/**
 * @brief ViewStart::about : Créer un QMessageBox, qui affiche des informations sur la création du jeu
 */
void ViewStart::about(){

    QScreen * screen = QGuiApplication::primaryScreen();
    QMessageBox * msg = new QMessageBox(this);
    QAbstractButton * pButtonYes = msg->addButton(tr("yes"), QMessageBox::YesRole);

    msg->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    msg->setFont(QFont("Bradley Hand ITC", 13));
    msg->setStyleSheet("background-color: #2c91c8;");
    msg->setWindowTitle(tr("About"));
    msg->setText(tr("This application was created by JOUVIN Tanguy, HOGG Jack and GRENON Guillaume for our third-year internship"));
    pButtonYes->setStyleSheet("background-color: #4CD80F;");
    pButtonYes->setFont(QFont("Bradley Hand ITC", 13));
    msg->adjustSize();
    msg->move(screen->geometry().center() - msg->rect().center());

    msg->exec();

}

/**
 * @brief ViewStart::help : Créer un QMessageBox, qui affiche les règles du jeu
 */
void ViewStart::help(){

    QScreen *screen = QGuiApplication::primaryScreen();
    QMessageBox *msg = new QMessageBox(this);
    QAbstractButton* pButtonYes = msg->addButton(tr("Got it !"), QMessageBox::YesRole);

    msg->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    msg->setFont(QFont("Bradley Hand ITC", 13));
    msg->setStyleSheet("background-color: #2c91c8;");
    msg->setWindowTitle(tr("Help"));
    msg->setText(tr("- The right and left arrows on the keyboard allow you to change monsters.\n"
                    "- Return key allows you to select a monster.\n"
                    "- Once selected the right, left, down and up key allows you to choose where you can play.\n\n"
                    "Special attack :\n"
                    "\t Tank : increase its own defense.\n"
                    "\t Rogue : attack all enemies that within range.\n"
                    "\t Warrior : increase its own attack.\n"
                    "\t Wizard : Heal his allies or him.\n\n"
                    "Principle :\n"
                    "\t The goal is to kill all enemies.\n"
                    "\t You have 40 seconds to play until your turn passes."));
    pButtonYes->setStyleSheet("background-color: #4CD80F;");
    pButtonYes->setFont(QFont("Bradley Hand ITC", 13));
    msg->adjustSize();
    msg->move(screen->geometry().center() - msg->rect().center());

    msg->exec();

}

/**
 * @brief ViewStart::~ViewStart : Destructeur
 */
ViewStart::~ViewStart()
{
    delete ui;
}

/**
 * @brief ViewStart::on_PlayButton_clicked : émets deux signaux lorsque l'on clique sur le bouton play
 */
void ViewStart::on_PlayButton_clicked()
{
    emit updateUserName(ui->TextUserName->text());

    if(ui->ListDifficulty->currentText() == "Easy")
        emit updateDifficulty(Difficulty::Easy);
    else if(ui->ListDifficulty->currentText() == "Medium")
        emit updateDifficulty(Difficulty::Medium);
    else if(ui->ListDifficulty->currentText() == "Hard")
        emit updateDifficulty(Difficulty::Hard);

    emit play();
}
