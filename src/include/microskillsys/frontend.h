#ifndef MICROSKILLSYS_FRONTEND_H
#define MICROSKILLSYS_FRONTEND_H

#include "battle.h"

// Compute the battle round order.
void populateRoundOrder(struct BattleUnit *initiator, struct BattleUnit *target);

// Compute the basic combat statistics. VERY EXPERT.
// Don't change this unless you intend to change the formulas used to compute
// the basic combat stats (such as changing which stat is used for avoid
// calculation, or changing the effectiveness coefficient). These should not
// floor stats to 0.
void populateBaseStats(struct BattleUnit *unit, struct BattleUnit *opponent);

// Compute any bonuses on combatant stats. Prefer this over `populateBaseStats`
// if possible.
void populateCombatBonuses(
    struct BattleUnit *unit, struct BattleUnit *opponent, struct InCombatBonuses *out
);

// Compute any mods on the final battle results (proc skills).
void populateRoundResult(
    struct BattleUnit *attacker, struct BattleUnit *defender, struct RoundResult *out
);

#ifndef NO_MICROSKILLSYS_STATSCREEN

// TODO (cam): Rethink this design. Separating `populateSkillIconList` and
// `getNthSkillText` doesn't make sense, instead `initSkillDisplay` should
// populate some intermediate list of skill ids.

// Given a unit, initialize any info needed to later display skills properly.
// This is called when the unit stat screen is initially loaded. It can be
// used to store information about the
// This is usually used to load the list of skills a unit has into memory for
// easy lookup by `getNthSkillText`.
void initSkillDisplay(struct Unit *unit);

// Return the list of icons to display, as indexes into the skill icon table.
void populateSkillIconList(struct Unit *unit, int *icons);

// Return the description of the unit's nth skill. Return -1 if there is no
// such skill.
short getNthSkillText(struct Unit *unit, int index);

#endif

#endif
