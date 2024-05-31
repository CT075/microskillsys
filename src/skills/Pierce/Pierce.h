#ifndef MICROSKILLSYS_PIERCE
#define MICROSKILLSYS_PIERCE

#include "bmunit.h"
#include "microskillsys/battle_simple.h"

bool hasPierce(struct Unit *unit);

int PierceProcRate(struct BattleUnit *bu);

void applyPierce(
    struct BattleUnit *attacker, struct BattleUnit *defender, struct RoundResult *result
);

#endif
