#include "global.h"

#include "bmitem.h"
#include "bmunit.h"
#include "constants/characters.h"
#include "variables.h"

#include "microskillsys/battle_simple.h"
#include "microskillsys/battleunit_calc.h"

#define CHARACTER_MATTHEW CHARACTER_COLM
#define CHARACTER_EPHIDEL CHARACTER_LYON

bool hasRevenger(struct Unit *unit) { return UNIT_CHAR_ID(unit) == CHARACTER_MATTHEW; }

void applyRevengerCombatBuffs(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods
) {
  if (UNIT_CHAR_ID(&opponent->unit) != CHARACTER_EPHIDEL) {
    return;
  }

  mods->avoMod += 30;
  mods->critMod += 30;
}

int RevengerProcRate(struct BattleUnit *bu) { return 100; }

void applyRevengerProc(
    struct BattleUnit *attacker, struct BattleUnit *defender, struct RoundResult *result
) {
  if (UNIT_CHAR_ID(&defender->unit) == CHARACTER_EPHIDEL) {
    result->didAttackerProcSkill = true;
    if (!result->didAttackCrit) {
      result->finalDamage *= 3;
      result->didAttackCrit = true;
    }
  }
}

// CR cam: This shouldn't live here
s8 isUnitEffectiveAgainst(struct Unit *actor, struct Unit *target) {
  int actorClass = actor->pClassData->number;
  int targetClass = target->pClassData->number;

  const u8 *effList = NULL;

  switch (actorClass) {

  case 0x2B:
  case 0x2C:
    effList = ItemEffectiveness_Monsters;
    break;

  } // switch (actorClass)

  if (!effList)
    return FALSE;

  for (; *effList; ++effList)
    if (*effList == targetClass)
      // NOTE: see note in IsItemEffectiveAgainst
      goto is_effective;

  return FALSE;

is_effective:
  return TRUE;
}

s8 IsUnitEffectiveAgainst(struct Unit *actor, struct Unit *target) {
  if (UNIT_CHAR_ID(actor) == CHARACTER_MATTHEW &&
      UNIT_CHAR_ID(target) == CHARACTER_EPHIDEL) {
    return TRUE;
  }

  return isUnitEffectiveAgainst(actor, target);
}
