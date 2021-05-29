#ifndef CHOOSE_HPP
#define CHOOSE_HPP

#include <QVector>
#include <QString>
#include <Models/Pawns/pawn.h>
#include "Models/Pawns/monster_warrior_.h"
#include "Models/Pawns/monster_wizard_.h"
#include "Models/Pawns/monster_rogue_.h"
#include "Models/Pawns/monster_tank_.h"

/**
 * @brief The Choose class
 */
class Choose
{
private:
    void loadPions();

    QVector<std::shared_ptr<Pawn> > _listPawns;

public:
    Choose();
    Choose(const Choose &c);
    ~Choose();

    QVector<std::shared_ptr<Pawn>> getListPawns() const;

    void operator=(const Choose &c);
};

#endif // CHOOSE_HPP
