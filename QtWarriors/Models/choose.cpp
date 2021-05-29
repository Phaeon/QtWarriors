#include "choose.hpp"

/**
 * @brief Choose::Choose : Instancie un objet Choose
 */
Choose::Choose()
    : _listPawns()
{
    loadPions();
}

/**
 * @brief Choose::Choose : Constructeur par recopie de Choose
 * @param c : Objet Choose
 */
Choose::Choose(const Choose &c)
    : _listPawns()
{
    for(const auto &i : c._listPawns)
        this->_listPawns.push_back(i);
}

/**
 * @brief Choose::operator = : Opérateur d'affectation
 * @param c : Objet Choose
 */
void Choose::operator=(const Choose &c)
{
    _listPawns.clear();
    for(const auto &i : c._listPawns)
        this->_listPawns.push_back(i);

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
    _listPawns.push_back(std::make_shared<Monster_ROGUE_>(10, 8, true));
    _listPawns.push_back(std::make_shared<Monster_TANK_>(10, 6, true));
    _listPawns.push_back(std::make_shared<Monster_WARRIOR_>(10, 4, true));
    _listPawns.push_back(std::make_shared<Monster_WIZARD_>(10, 2, true));
}

/**
 * @brief Choose::getListPawns
 * @return Une liste de Pawn
 */
QVector<std::shared_ptr<Pawn>> Choose::getListPawns() const
{
    return this->_listPawns;
}
