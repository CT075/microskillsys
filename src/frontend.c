#include "bmbattle.h"
#include "bmitem.h"
#include "bmunit.h"

#include "microskillsys/battle.h"
#include "microskillsys/battleunit_calc.h"
#include "microskillsys/frontend.h"

#include "microskillsys/buffs.h"

void populateRoundOrder(struct BattleUnit *initiator, struct BattleUnit *target) {
  defaultPopulateRoundOrder(initiator, target);
}

void populateRoundResult(
    struct BattleUnit *attacker, struct BattleUnit *defender, struct RoundResult *out
) {
  defaultPopulateRoundResult(attacker, defender, out);
}

void populateBaseStats(struct BattleUnit *bu, struct BattleUnit *opponent) {
  struct BattleStatGetters getters;

  defaultPopulateBattleStatGetters(&getters);

  getters.computeAttack(bu, opponent);
  getters.computeDefense(opponent, bu);
  getters.computeSpeed(bu);
  getters.computeHit(bu);
  getters.computeAvoid(bu);
  getters.computeCrit(bu);
  getters.computeDodge(bu);
  getters.computeSupportBonuses(bu, opponent);
  getters.computeWeaponRankBonuses(bu);
  getters.computeStatusBonuses(bu);
}

void populateCombatBonuses(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods
) {
  // do nothing
  return;
}

int unitPowBuff(struct Unit *unit) {
  return 0;
}

int unitSklBuff(struct Unit *unit) {
  return 0;
}

int unitSpdBuff(struct Unit *unit) {
  return 0;
}

int unitDefBuff(struct Unit *unit) {
  return 0;
}

int unitResBuff(struct Unit *unit) {
  return 0;
}

int unitLckBuff(struct Unit *unit) {
  return 0;
}

void initSkillDisplay(struct Unit *unit) {
  return;
}

void populateSkillIconList(struct Unit *unit, int *icons) {
  return;
}

short getNthSkillText(struct Unit *unit, int index) {
  return -1;
}
