#ifndef MICROSKILLSYS_BATTLEUNIT_CALC_H
#define MICROSKILLSYS_BATTLEUNIT_CALC_H

#include "bmbattle.h"
#include "microskillsys/battle.h"

struct BattleStatGetters {
  void (*computeAttack)(struct BattleUnit *bu, struct BattleUnit *opponent);
  // WARNING: Note that we compute defense for the opponent, not the primary unit!
  void (*computeDefense)(struct BattleUnit *opponent, struct BattleUnit *bu);
  void (*computeSpeed)(struct BattleUnit *bu);
  // These three should be *unfloored* (that is, return a negative number if
  // necessary). We will floor to 0 later.
  void (*computeHit)(struct BattleUnit *bu);
  // This uses the modded speed above
  void (*computeAvoid)(struct BattleUnit *bu);
  void (*computeCrit)(struct BattleUnit *bu);
  void (*computeDodge)(struct BattleUnit *bu);
  void (*computeSupportBonuses)(struct BattleUnit *bu, struct BattleUnit *opponent);
  void (*computeWeaponRankBonuses)(struct BattleUnit *bu);
  void (*computeStatusBonuses)(struct BattleUnit *bu);
};

// CR cam: move this into a separate frontend
void populateBattleStatGettersForUnit(struct Unit *unit, struct BattleStatGetters *getters);

void defaultPopulateBattleStatGetters(struct BattleStatGetters *out);

struct CalcModSkillSpec {
  bool (*applies)(struct Unit *unit);
  void (*apply)(struct BattleStatGetters *out);
};

#endif
