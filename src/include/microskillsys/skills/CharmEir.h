#ifndef MICROSKILLSYS_CHARM_EIR_H
#define MICROSKILLSYS_CHARM_EIR_H

#include "bmunit.h"
#include "bmbattle.h"

#include "microskillsys/battle_simple.h"

bool CharmEirApplies(struct Unit *);
void applyCharmEir(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods
);

#endif
