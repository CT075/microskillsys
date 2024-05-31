#ifndef MICROSKILLSYS_AEGIS_H
#define MICROSKILLSYS_AEGIS_H

#include "bmunit.h"
#include "microskillsys/battle_simple.h"

bool hasAegis(struct Unit *unit);
int AegisProcRate(struct BattleUnit *bu);
void applyAegis(
    struct BattleUnit *attacker, struct BattleUnit *defender, struct RoundResult *result
);

#endif
