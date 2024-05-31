#include "bmitem.h"
#include "bmunit.h"
#include "constants/classes.h"
#include "constants/items.h"

#include "Aegis.h"
#include "microskillsys/battle.h"
#include "microskillsys/battle_simple.h"

bool hasAegis(struct Unit *unit) { return UNIT_CLASS_ID(unit) == CLASS_PALADIN; }

int AegisProcRate(struct BattleUnit *bu) {
  return GetUnitSkill(&bu->unit) + bu->unit.level;
}

void applyAegis(
    struct BattleUnit *attacker, struct BattleUnit *defender, struct RoundResult *result
) {
  result->didDefenderProcSkill = true;
  result->finalDamage /= 2;
}
