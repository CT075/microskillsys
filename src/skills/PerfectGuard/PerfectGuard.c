#include "bmitem.h"
#include "bmunit.h"
#include "constants/characters.h"
#include "constants/classes.h"
#include "constants/items.h"

#include "PerfectGuard.h"
#include "microskillsys/battle.h"
#include "microskillsys/battle_simple.h"

bool hasPerfectGuard(struct Unit *unit) { return UNIT_CLASS_ID(unit) == CLASS_GENERAL; }

int PerfectGuardProcRate(struct BattleUnit *bu) {
  if (UNIT_CHAR_ID(&bu->unit) == CHARACTER_GILLIAM) {
    return 100;
  }
  return GetUnitSkill(&bu->unit) / 2;
}

void applyPerfectGuard(
    struct BattleUnit *attacker, struct BattleUnit *defender, struct RoundResult *result
) {
  result->didDefenderProcSkill = true;
  result->finalDamage = 0;
}
