#include "bmitem.h"
#include "bmunit.h"
#include "constants/characters.h"
#include "global.h"

#include "CharmEir.h"
#include "microskillsys/battle.h"
#include "microskillsys/battle_simple.h"

bool CharmEirApplies(struct Unit *unit) {
  if (UNIT_CHAR_ID(unit) == CHARACTER_EIRIKA) {
    return false;
  }

  struct Unit *eirika = gUnitLookup[CHARACTER_EIRIKA];

  return ABS(eirika->xPos - unit->xPos) + ABS(eirika->yPos - unit->yPos) <= 2;
}

void applyCharmEir(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods
) {
  mods->avoMod += 10;
  mods->critMod += 10;
}
