#include "bmbattle.h"
#include "bmitem.h"
#include "bmunit.h"
#include "constants/characters.h"
#include "constants/classes.h"
#include "constants/items.h"

#include "ParseDefinitions.event.h"
#include "constants.h"
#include "microskillsys/battle.h"
#include "microskillsys/constants.h"
#include "microskillsys/frontend.h"

#include "microskillsys/battle_simple.h"
#include "microskillsys/battleunit_calc.h"
#include "microskillsys/buffs.h"
#include "microskillsys/icons.h"
#include "microskillsys/skills.h"

#define NUM_CALC_SKILLS (sizeof(calcSkills) / sizeof(struct CalcModSkillSpec))

const struct CalcModSkillSpec calcSkills[] = {
  { hasShootDown, applyShootDown },
  { hasCovert, applyCovert },
};

#define NUM_PRE_BATTLE_SPECS                                                           \
  (sizeof(simpleSkills) / sizeof(struct SimplePreBattleSkillSpec))

// CR cam: generate this
const struct SimplePreBattleSkillSpec simpleSkills[] = {
  { hasShootDown, applyShootDownHitBonus },
  { recklessMayApply, applyReckless },
  { hasTrample, applyTrample },
  { hasAirSuperiority, applyAirSuperiority },
  { CharmEirApplies, applyCharmEir },
  { hasCharmEph, applyCharmEph },
  { hasRevenger, applyRevengerCombatBuffs },
  { hasSmite, applySmite },
};

#define NUM_PROC_SKILLS (sizeof(procSkills) / sizeof(struct ProcSkillSpec))

// CR cam: Maybe it'd be better to split into attacker/defender instead of
// using the enum?
const struct ProcSkillSpec procSkills[] = {
  {
      Attacker,
      hasPierce,
      PierceProcRate,
      applyPierce,
  },
  {
      Defender,
      hasPerfectGuard,
      PerfectGuardProcRate,
      applyPerfectGuard,
  },
  { Attacker, hasRevenger, RevengerProcRate, applyRevengerProc },
};

void populateRoundOrder(struct BattleUnit *initiator, struct BattleUnit *target) {
  defaultPopulateRoundOrder(initiator, target);
}

void populateRoundResult(
    struct BattleUnit *attacker, struct BattleUnit *defender, struct RoundResult *out
) {
  defaultPopulateRoundResult(attacker, defender, out);

  for (int i = 0; i < NUM_PROC_SKILLS; i += 1) {
    struct BattleUnit *bu = attacker;
    struct ProcSkillSpec skill = procSkills[i];
    switch (skill.side) {
    case Attacker:
      bu = attacker;
      break;
    case Defender:
      bu = defender;
      break;
    }
    if (skill.canProc(&bu->unit)) {
      int rate = skill.procRate(bu);
      if (BattleRoll1RN(rate, FALSE)) {
        skill.apply(attacker, defender, out);
      }
    }
  }
}

void populateBaseStats(struct BattleUnit *bu, struct BattleUnit *opponent) {
  struct BattleStatGetters getters;

  defaultPopulateBattleStatGetters(&getters);

  for (int i = 0; i < NUM_CALC_SKILLS; i += 1) {
    struct CalcModSkillSpec skill = calcSkills[i];
    if (skill.applies(&bu->unit)) {
      skill.apply(&getters);
    }
  }

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
  if (hasNihil(&opponent->unit)) {
    return;
  }

  for (int i = 0; i < NUM_PRE_BATTLE_SPECS; i += 1) {
    struct SimplePreBattleSkillSpec skill = simpleSkills[i];
    if (skill.applies(&bu->unit)) {
      skill.apply(bu, opponent, mods);
    }
  }
}

// CR cam: Is there some better way to express this?
void ComputeBattleUnitEffectiveHitRate(
    struct BattleUnit *attacker, struct BattleUnit *defender
) {
  if (hasNoGuard(&attacker->unit) || hasNoGuard(&defender->unit)) {
    attacker->battleEffectiveHitRate = 100;
  }
  else {
    attacker->battleEffectiveHitRate =
        attacker->battleHitRate - defender->battleAvoidRate;
  }

  if (attacker->battleEffectiveHitRate > 100) {
    attacker->battleEffectiveHitRate = 100;
  }

  if (attacker->battleEffectiveHitRate < 0) {
    attacker->battleEffectiveHitRate = 0;
  }
}

int unitPowBuff(struct Unit *unit) {
  if (UNIT_CHAR_ID(unit) == CHARACTER_LYON) {
    return CountRedUnits() / 2;
  }
  return 0;
}

int unitSklBuff(struct Unit *unit) {
  if (UNIT_CHAR_ID(unit) == CHARACTER_LYON) {
    return CountRedUnits() / 2;
  }
  return 0;
}

int unitSpdBuff(struct Unit *unit) {
  if (UNIT_CHAR_ID(unit) == CHARACTER_LYON) {
    return CountRedUnits() / 2;
  }
  return 0;
}

int unitDefBuff(struct Unit *unit) {
  if (UNIT_CHAR_ID(unit) == CHARACTER_LYON) {
    return CountRedUnits() / 2;
  }
  return 0;
}

int unitResBuff(struct Unit *unit) {
  if (UNIT_CHAR_ID(unit) == CHARACTER_LYON) {
    return CountRedUnits() / 2;
  }
  return 0;
}

int unitLckBuff(struct Unit *unit) {
  if (UNIT_CHAR_ID(unit) == CHARACTER_LYON) {
    return CountRedUnits() / 2;
  }
  return 0;
}

// CR cam: de-dup the text tables from the icon tables

short getCharacterSkillText(struct Unit *unit) {
  // CR cam: populate this
  switch (UNIT_CHAR_ID(unit)) {
  case CHARACTER_LYON:
    return AllForOneDesc;
  case CHARACTER_COLM:
    return RevengerDesc;
  }

  return -1;
}

short getClassSkillText(struct Unit *unit) {
  switch (UNIT_CLASS_ID(unit)) {
  case CLASS_PALADIN:
    return AegisDesc;
  case CLASS_FALCON_KNIGHT:
    return AirSuperiorityDesc;
  case CLASS_WARRIOR:
    return NoGuardDesc;
  case CLASS_GENERAL:
    return PerfectGuardDesc;
  case CLASS_WYVERN_LORD:
    return PierceDesc;
  case CLASS_BERSERKER:
    return RecklessDesc;
  case CLASS_SNIPER:
    return ShootDownDesc;
  case CLASS_GREAT_KNIGHT:
    return TrampleDesc;
  case CLASS_EIRIKA_MASTER_LORD:
    return CharmEirDesc;
  case CLASS_EPHRAIM_MASTER_LORD:
    return CharmEphDesc;
  case CLASS_ROGUE:
    return CovertDesc;
  case CLASS_WYVERN_KNIGHT:
    return AirRaidDesc;
  case CLASS_BISHOP:
    return SlayerDesc;
  }

  return -1;
}

short getCharacterSkillIcon(struct Unit *unit) {
  // CR cam: populate this
  switch (UNIT_CHAR_ID(unit)) {
  case CHARACTER_LYON:
    return AllForOneIconId;
  case CHARACTER_COLM:
    return RevengerIconId;
  case CHARACTER_LARACHEL:
    return SmiteIconId;
  }

  return -1;
}

short getClassSkillIcon(struct Unit *unit) {
  switch (UNIT_CLASS_ID(unit)) {
  case CLASS_PALADIN:
    return AegisIconId;
  case CLASS_FALCON_KNIGHT:
    return AirSuperiorityIconId;
  case CLASS_WARRIOR:
    return NoGuardIconId;
  case CLASS_GENERAL:
    return PerfectGuardIconId;
  case CLASS_WYVERN_LORD:
    return PierceIconId;
  case CLASS_BERSERKER:
    return RecklessIconId;
  case CLASS_SNIPER:
    return ShootDownIconId;
  case CLASS_GREAT_KNIGHT:
    return TrampleIconId;
  case CLASS_EIRIKA_MASTER_LORD:
    return CharmEirIconId;
  case CLASS_EPHRAIM_MASTER_LORD:
    return CharmEphIconId;
  case CLASS_ROGUE:
    return CovertIconId;
  case CLASS_WYVERN_KNIGHT:
    return AirRaidIconId;
  case CLASS_BISHOP:
    return SlayerIconId;
  }

  return -1;
}

void initSkillDisplay(struct Unit *unit) {
  for (int i = 0; i < MAX_SKILLS_POSSIBLE; i += 1) {
    gSkillTextIdBuffer[i] = -1;
  }

  int index = 0;
  short result;

  if ((result = getCharacterSkillText(unit)) != -1) {
    gSkillTextIdBuffer[index] = result;
    index += 1;
  }

  if ((result = getClassSkillText(unit)) != -1) {
    gSkillTextIdBuffer[index] = result;
    index += 1;
  }
}

void populateSkillIconList(struct Unit *unit, int *icons) {
  int index = 0;
  short result;

  if ((result = getCharacterSkillIcon(unit)) != -1) {
    icons[index] = result;
    index += 1;
  }

  if ((result = getClassSkillIcon(unit)) != -1) {
    icons[index] = result;
    index += 1;
  }
}

short getNthSkillText(struct Unit *unit, int index) {
  return gSkillTextIdBuffer[index];
}
