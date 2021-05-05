#include "start.hpp"

/**
 * @brief Start::Start : Instancie un objet Start
 * @param name : Nom du joueur
 * @param difficulty : Difficulté de la partie
 */
Start::Start(const QString &name, Difficulty difficulty)
    : _Name(name), _Difficulty(difficulty)
{}

/**
 * @brief Start::Start : Constructeur par défaut
 */
Start::Start()
    : _Name("Team Guest"), _Difficulty(Difficulty::Medium)
{}

/**
 * @brief Start::Start : Constructeur par recopie de Start
 * @param s : Objet Start
 */
Start::Start(const Start &s)
{
    this->_Name = s._Name;
    this->_Difficulty = s._Difficulty;
}

/**
 * @brief Start::operator = : Opérateur d'affectation
 * @param s : Objet Start
 */
void Start::operator=(const Start &s)
{
    this->_Name = s._Name;
    this->_Difficulty = s._Difficulty;
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
    return this->_Name;
}

/**
 * @brief Start::setName : Change de le nom du joueur
 * @param name : nom du joueur
 */
void Start::setName(const QString &name){
    this->_Name = (name != "") ? "Team " + name : "Team Guest";
}

/**
 * @brief Start::setDifficulty : Change la difficulté de la partie
 * @param difficulty : Difficulté de la partie
 */
void Start::setDifficulty(Difficulty difficulty)
{
    this->_Difficulty = difficulty;
}
