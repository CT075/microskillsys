#ifndef MICROSKILLSYS_SHOOT_DOWN_H
#define MICROSKILLSYS_SHOOT_DOWN_H

#include "bmunit.h"
#include "microskillsys/battle_simple.h"
#include "microskillsys/battleunit_calc.h"

bool hasShootDown(struct Unit *unit);
void applyShootDown(struct BattleStatGetters *getters);
void applyShootDownHitBonus(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods
);

#endif
