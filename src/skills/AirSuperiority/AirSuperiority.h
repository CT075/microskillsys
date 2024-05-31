#ifndef MICROSKILLSYS_AIR_SUPERIORITY
#define MICROSKILLSYS_AIR_SUPERIORITY

#include "bmunit.h"
#include "microskillsys/battle_simple.h"

bool hasAirSuperiority(struct Unit *);
void applyAirSuperiority(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods
);

#endif
