#ifndef MICROSKILLSYS_SMITE_H
#define MICROSKILLSYS_SMITE_H

#include "bmunit.h"
#include "microskillsys/battle_simple.h"

bool hasSmite(struct Unit *unit);
void applySmite(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods
);

#endif
