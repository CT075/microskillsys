#include "bmitem.h"
#include "bmunit.h"
#include "constants/classes.h"
#include "constants/items.h"

#include "AirRaid.h"
#include "microskillsys/battle.h"
#include "microskillsys/battle_simple.h"

bool hasAirRaid(struct Unit *unit) {
  return unit->pClassData->number == CLASS_WYVERN_KNIGHT;
}

void applyAirRaid(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods
) {
  if (opponent->unit.pClassData->pMovCostTable[0][bu->terrainId] == -1) {
    return;
  }
  mods->speedMod += 5;
  mods->avoMod += 10;
}
