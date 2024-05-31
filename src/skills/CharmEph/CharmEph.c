#include "bmitem.h"
#include "bmmap.h"
#include "bmunit.h"
#include "constants/characters.h"
#include "global.h"

#include "CharmEph.h"
#include "microskillsys/battle.h"
#include "microskillsys/battle_simple.h"

bool hasCharmEph(struct Unit *unit) { return UNIT_CHAR_ID(unit) == CHARACTER_EPHRAIM; }

bool isPlayerUnitAtCoords(int x, int y) {
  u8 bmMapUnit = gBmMapUnit[y][x];
  if (!bmMapUnit) {
    return false;
  }
  struct Unit *unit = GetUnit(bmMapUnit);

  return UNIT_FACTION(unit) == FACTION_BLUE;
}

const struct Vec2 points[] = {
  { 0, 2 },  { -1, 1 }, { 0, 1 },   { 1, 1 },  { 2, 0 },  { 1, 0 },
  { -1, 0 }, { -2, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { 2, 0 },
};

#define NUM_POINTS (sizeof(points) / sizeof(struct Vec2))

void applyCharmEph(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods
) {
  int x = bu->unit.xPos;
  int y = bu->unit.yPos;

  for (int i = 0; i < NUM_POINTS; i += 1) {
    if (isPlayerUnitAtCoords(x + points[i].x, y + points[i].y)) {
      mods->avoMod += 5;
      mods->critMod += 5;
    }
  }
}
