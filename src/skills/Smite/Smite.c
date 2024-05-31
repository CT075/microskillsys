#include "bmitem.h"
#include "bmunit.h"
#include "constants/characters.h"
#include "constants/items.h"

#include "Smite.h"
#include "microskillsys/battle.h"
#include "microskillsys/battle_simple.h"

bool hasSmite(struct Unit *unit) {
  return unit->pCharacterData->number == CHARACTER_LARACHEL;
}

void applySmite(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods
) {
  switch (ITEM_INDEX(bu->weapon)) {
  case ITEM_ANIMA_THUNDER:
  case ITEM_ANIMA_BOLTING:
    mods->attackMod += 10;
    mods->critMod += 30;
    break;
  }
}
