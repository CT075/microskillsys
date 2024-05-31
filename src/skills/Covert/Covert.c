#include "bmitem.h"
#include "bmunit.h"
#include "constants/classes.h"

#include "microskillsys/battle_simple.h"
#include "microskillsys/battleunit_calc.h"

bool hasCovert(struct Unit *unit) { return UNIT_CLASS_ID(unit) == CLASS_ROGUE; }

void covertAvoRate(struct BattleUnit *bu) {
  bu->battleAvoidRate = (bu->battleSpeed * 2) + (bu->terrainAvoid * 2) + bu->unit.lck;
}

void covertDefense(struct BattleUnit *bu, struct BattleUnit *opponent) {
  if (GetItemAttributes(opponent->weapon) & IA_MAGICDAMAGE)
    bu->battleDefense = (bu->terrainResistance * 2) + bu->unit.res;
  else if (GetItemAttributes(opponent->weapon) & IA_MAGIC)
    bu->battleDefense = (bu->terrainResistance * 2) + bu->unit.res;
  else
    bu->battleDefense = (bu->terrainDefense * 2) + bu->unit.def;
}

void applyCovert(struct BattleStatGetters *getters) {
  getters->computeAvoid = covertAvoRate;
  getters->computeDefense = covertDefense;
}
