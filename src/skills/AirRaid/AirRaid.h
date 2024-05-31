#ifndef MICROSKILLSYS_AIR_RAID_H
#define MICROSKILLSYS_AIR_RAID_H

#include "bmunit.h"
#include "microskillsys/battleunit_calc.h"

bool hasAirRaid(struct Unit *);
void applyAirRaid(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods
);

#endif
