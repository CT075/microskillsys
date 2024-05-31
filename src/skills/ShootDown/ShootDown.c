#include "bmitem.h"
#include "bmunit.h"
#include "constants/classes.h"
#include "constants/items.h"

#include "ShootDown.h"
#include "microskillsys/battle.h"
#include "microskillsys/battle_simple.h"
#include "microskillsys/battleunit_calc.h"

bool hasShootDown(struct Unit *unit) {
  return unit->pClassData->number == CLASS_SNIPER;
}

// CR cam: it'd be nice to not have to reproduce the entirety of
// ComputeBattleUnitAttack here.
void computeAttackWithShootDown(struct BattleUnit *bu, struct BattleUnit *opponent) {
  bu->battleAttack = GetItemMight(bu->weapon) + bu->wTriangleDmgBonus;

  // Check Iron Bow specifically because Vidofnir is also effective vs monsters
  if (IsItemEffectiveAgainst(ITEM_BOW_IRON, &opponent->unit)) {
    bu->battleAttack *= 5;
  }
  else if (GetItemIndex(bu->weapon) == ITEM_BOW_NIDHOGG) {
    bu->battleAttack *= 2;
  }

  bu->battleAttack += bu->unit.pow;

  if (GetItemIndex(bu->weapon) == ITEM_MONSTER_STONE) {
    bu->battleAttack = 0;
  }
}

void applyShootDown(struct BattleStatGetters *getters) {
  getters->computeAttack = computeAttackWithShootDown;
}

void applyShootDownHitBonus(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods
) {
  if (IsItemEffectiveAgainst(ITEM_BOW_IRON, &opponent->unit)) {
    mods->hitMod += 30;
  }
}
