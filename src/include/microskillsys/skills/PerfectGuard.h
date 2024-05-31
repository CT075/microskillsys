#ifndef MICROSKILLSYS_PERFECT_GUARD_H
#define MICROSKILLSYS_PERFECT_GUARD_H

#include "bmunit.h"
#include "microskillsys/battle_simple.h"

bool hasPerfectGuard(struct Unit *unit);
int PerfectGuardProcRate(struct BattleUnit *bu);
void applyPerfectGuard(
    struct BattleUnit *attacker, struct BattleUnit *defender, struct RoundResult *result
);

#endif
