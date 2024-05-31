#include "bmitem.h"
#include "bmunit.h"
#include "constants/classes.h"
#include "constants/items.h"

#include "Trample.h"
#include "microskillsys/battle.h"
#include "microskillsys/battle_simple.h"

bool hasTrample(struct Unit *unit) {
  return unit->pClassData->number == CLASS_GREAT_KNIGHT;
}

void applyTrample(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods
) {
  // We define "non-mounted" as "neither on horseback nor flying". The quick
  // and dirty way to determine this is to check if the opponent is weak to
  // Horseslayer or Iron Bow, respectively.

  if (IsItemEffectiveAgainst(ITEM_BOW_IRON, &opponent->unit)) {
    return;
  }

  if (IsItemEffectiveAgainst(ITEM_LANCE_HORSESLAYER, &opponent->unit)) {
    return;
  }

  if (gBattleStats.range != 1) {
    return;
  }

  mods->attackMod += 5;
}
