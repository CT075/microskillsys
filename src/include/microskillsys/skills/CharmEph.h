#ifndef MICROSKILLSYS_CHARM_EPH_H
#define MICROSKILLSYS_CHARM_EPH_H

#include "bmunit.h"
#include "bmbattle.h"

#include "microskillsys/battle_simple.h"

bool hasCharmEph(struct Unit *);
void applyCharmEph(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods
);

#endif
