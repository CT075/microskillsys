#ifndef MICROSKILLSYS_FRONTEND_H
#define MICROSKILLSYS_FRONTEND_H

#include "battle.h"

// Given a unit, initialize any info needed to later display skills properly.
// This is usually used to load the list of skills a unit has into memory for
// easy lookup by `getNthSkillText`.
void initSkillDisplay(struct Unit *unit);

// Return the list of icons to display, as indexes into the skill icon table.
void populateSkillIconList(struct Unit *unit, int *icons);

// Return the description of the nth skill in the list.
short getNthSkillText(struct Unit *unit, int index);

// Compute the battle round order
void populateRoundOrder(struct BattleUnit *initiator, struct BattleUnit *target);

// Compute the basic combat statistics. VERY EXPERT.
// Don't change this unless you intend to change the formulas used to compute
// the basic combat stats (such as changing which stat is used for avoid
// calculation, or changing the effectiveness coefficient). These should not
// cap stats at 0.
void populateBaseStats(struct BattleUnit *unit, struct BattleUnit *opponent);

// Compute any bonuses on combatant stats. Prefer this over `populateBaseStats`
// if possible.
void populateCombatBonuses(
    struct BattleUnit *unit, struct BattleUnit *opponent, struct InCombatBonuses *out
);

// Compute any mods on the final battle results
void populateRoundResult(
    struct BattleUnit *attacker, struct BattleUnit *defender, struct RoundResult *out
);

#endif
