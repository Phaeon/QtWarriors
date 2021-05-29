#include "start.hpp"

/**
 * @brief Start::Start : Instancie un objet Start
 * @param name : Nom du joueur
 * @param difficulty : Difficulté de la partie
 */
Start::Start(const QString &name, Difficulty difficulty)
    : _name(name), _difficulty(difficulty)
{}

/**
 * @brief Start::Start : Constructeur par défaut
 */
Start::Start()
    : _name("Team Guest"), _difficulty(Difficulty::Medium)
{}

/**
 * @brief Start::Start : Constructeur par recopie de Start
 * @param s : Objet Start
 */
Start::Start(const Start &s)
{
    this->_name = s._name;
    this->_difficulty = s._difficulty;
}

/**
 * @brief Start::operator = : Opérateur d'affectation
 * @param s : Objet Start
 */
void Start::operator=(const Start &s)
{
    this->_name = s._name;
    this->_difficulty = s._difficulty;
}

/**
 * @brief Start::~Start : Destructeur
 */
Start::~Start()
{}

/**
 * @brief Start::getName
 * @return Le nom du joueur
 */
QString Start::getName() const
{
    return this->_name;
}

/**
 * @brief Start::setName : Change de le nom du joueur
 * @param name : nom du joueur
 */
void Start::setName(const QString &name){
    this->_name = (name != "") ? "Team " + name : "Team Guest";
}

/**
 * @brief Start::setDifficulty : Change la difficulté de la partie
 * @param difficulty : Difficulté de la partie
 */
void Start::setDifficulty(Difficulty difficulty)
{
    this->_difficulty = difficulty;
}

/**
 * @brief Start::getDifficulty
 * @return la difficulté
 */
Difficulty Start::getDifficulty() const
{
    return this->_difficulty;
}
