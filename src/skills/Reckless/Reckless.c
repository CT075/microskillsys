#include "bmunit.h"
#include "constants/classes.h"

#include "Reckless.h"

// CR cam: Implementing this skill is quite awkward with the existing interface.
// No time to re-engineer that before CELICA, but use this as a litmus test
// before releasing microskillsys for real

bool recklessMayApply(struct Unit *unit) { return true; }

void applyReckless(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods
) {
  // If both combatants have this skill, it should stack, so we have to check
  // both separately.

  if (UNIT_CLASS_ID(&bu->unit) == CLASS_BERSERKER) {
    mods->critMod += 30;
  }

  if (UNIT_CLASS_ID(&opponent->unit) == CLASS_BERSERKER) {
    mods->critMod += 30;
  }
}
