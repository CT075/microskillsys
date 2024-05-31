#ifndef MICROSKILLSYS_REVENGER_H
#define MICROSKILLSYS_REVENGER_H

#include "bmunit.h"
#include "microskillsys/battle_simple.h"
#include "microskillsys/battleunit_calc.h"

bool hasRevenger(struct Unit *unit);
void applyRevengerCombatBuffs(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods
);
int RevengerProcRate(struct BattleUnit *bu);
void applyRevengerProc(
    struct BattleUnit *attacker, struct BattleUnit *defender, struct RoundResult *result
);

#endif
