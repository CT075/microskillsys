#include "bmitem.h"
#include "bmunit.h"
#include "constants/classes.h"
#include "constants/items.h"

#include "AirSuperiority.h"
#include "microskillsys/battle.h"
#include "microskillsys/battle_simple.h"

bool hasAirSuperiority(struct Unit *unit) {
  return unit->pClassData->number == CLASS_FALCON_KNIGHT;
}

void applyAirSuperiority(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods
) {
  // We define "non-mounted" as "neither on horseback nor flying". The quick
  // and dirty way to determine this is to check if the opponent is weak to
  // Horseslayer or Iron Bow, respectively.

  if (IsItemEffectiveAgainst(ITEM_BOW_IRON, &opponent->unit)) {
    mods->avoMod += 20;
    mods->hitMod += 20;
    mods->critMod += 10;
  }
}
