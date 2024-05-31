#include "bmitem.h"
#include "bmunit.h"
#include "constants/classes.h"

#include "Pierce.h"
#include "microskillsys/battle.h"
#include "microskillsys/battle_simple.h"

bool hasPierce(struct Unit *unit) { return UNIT_CLASS_ID(unit) == CLASS_WYVERN_LORD; }

int PierceProcRate(struct BattleUnit *bu) { return GetUnitSkill(&bu->unit); }

void applyPierce(
    struct BattleUnit *attacker, struct BattleUnit *defender, struct RoundResult *result
) {
  result->didAttackerProcSkill = true;
  result->finalDamage = gBattleStats.attack;
}
