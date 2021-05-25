#include "choose.hpp"

/**
 * @brief Choose::Choose : Instancie un objet Choose
 */
Choose::Choose()
    : _listPions()
{
    loadPions();
}

/**
 * @brief Choose::Choose : Constructeur par recopie de Choose
 * @param c : Objet Choose
 */
Choose::Choose(const Choose &c)
    : _listPions()
{
    for(const auto &i : c._listPions)
        this->_listPions.push_back(i);
}

/**
 * @brief Choose::operator = : Opérateur d'affectation
 * @param c : Objet Choose
 */
void Choose::operator=(const Choose &c)
{
    _listPions.clear();
    for(const auto &i : c._listPions)
        this->_listPions.push_back(i);

}

/**
 * @brief Choose::~Choose : Destructeur
 */
Choose::~Choose()
{}

/**
 * @brief Choose::loadPions : Créer tous les monstres possibles et les mets dans un QVector
 */
void Choose::loadPions(){
    _listPions.push_back(std::make_shared<Monster_ROGUE_>(10, 10, true));
    _listPions.push_back(std::make_shared<Monster_TANK_>(10, 10, true));
    _listPions.push_back(std::make_shared<Monster_WARRIOR_>(10, 10, true));
    _listPions.push_back(std::make_shared<Monster_WIZARD_>(10, 10, true));
}

/**
 * @brief Choose::getListPions
 * @return Une liste de Pawn
 */
QVector<std::shared_ptr<Pawn>> Choose::getListPions() const
{
    return this->_listPions;
}