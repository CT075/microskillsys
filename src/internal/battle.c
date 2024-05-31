#include "global.h"

#include "bmbattle.h"
#include "bmitem.h"
#include "bmunit.h"
#include "constants/items.h"

#include "microskillsys/battle.h"
#include "microskillsys/battleunit_calc.h"
#include "microskillsys/frontend.h"
#include "ram_structures.h"

void clearRoundOrder(void) {
  for (int i = 0; i < MAX_BATTLE_ROUNDS; i += 1) {
    gBattleRoundOrder[i].turn = BattleOver;
  }
}

// CR cam: hook out
void setFollowup(
    struct BattleUnit *initiator, struct BattleUnit *target, struct BattleRound *out
) {
  if (target->battleSpeed > 250) {
    out->turn = BattleOver;
    return;
  }

  if (ABS(initiator->battleSpeed - target->battleSpeed) <
      BATTLE_FOLLOWUP_SPEED_THRESHOLD) {
    out->turn = BattleOver;
    return;
  }

  struct BattleUnit *lastRoundAttacker;

  if (initiator->battleSpeed > target->battleSpeed) {
    lastRoundAttacker = initiator;
    out->turn = InitiatorTurn;
  }
  else {
    lastRoundAttacker = target;
    out->turn = TargetTurn;
  }

  if (GetItemWeaponEffect(lastRoundAttacker->weaponBefore) == WPN_EFFECT_HPHALVE) {
    out->turn = BattleOver;
    return;
  }

  if (GetItemIndex(lastRoundAttacker->weapon) == ITEM_MONSTER_STONE) {
    out->turn = BattleOver;
    return;
  }

  out->count = 1 << BattleCheckBraveEffect(lastRoundAttacker);
}

// CR cam: rethink this design. this doesn't account for proc skills that
// may change the battle order. instead, have BattleGenerateHit return some
// info about the next round
void defaultPopulateRoundOrder(
    struct BattleUnit *initiator, struct BattleUnit *target
) {
  gBattleRoundOrder[0].turn = InitiatorTurn;
  gBattleRoundOrder[0].count = 1 << BattleCheckBraveEffect(initiator);
  gBattleRoundOrder[1].turn = TargetTurn;
  gBattleRoundOrder[1].count = 1 << BattleCheckBraveEffect(target);
  setFollowup(initiator, target, &gBattleRoundOrder[2]);
}

bool runBattleRound(
    struct BattleUnit *attacker, struct BattleUnit *defender, u32 count
) {
  if (!attacker->weapon) {
    return false;
  }

  for (int j = 0; j < count; j += 1) {
    if (BattleGenerateHit(attacker, defender)) {
      return true;
    }
  }

  return false;
}

void runBattleRounds(
    struct BattleUnit *initiator, struct BattleUnit *target, u16 attrs
) {
  for (int i = 0; i < MAX_BATTLE_ROUNDS; i += 1) {
    gBattleHitIterator->attributes |= attrs;
    switch (gBattleRoundOrder[i].turn) {
    case InitiatorTurn:
      if (runBattleRound(initiator, target, gBattleRoundOrder[i].count)) {
        return;
      }
      break;
    case TargetTurn:
      if (runBattleRound(target, initiator, gBattleRoundOrder[i].count)) {
        return;
      }
      break;
    case BattleOver:
      return;
    }
  }
}

void BattleUnwind(void) {
  ClearBattleHits();

  struct BattleUnit *initiator = &gBattleActor;
  struct BattleUnit *target = &gBattleTarget;

  populateRoundOrder(initiator, target);

  u16 attrs = gBattleHitIterator->attributes;

  gBattleHitIterator->info |= BATTLE_HIT_INFO_BEGIN;

  runBattleRounds(initiator, target, attrs);

  gBattleHitIterator->info |= BATTLE_HIT_INFO_END;
}

// CR cam: Maybe we should just remove the flooring inline?
void computeBattleUnitSpeedUnfloored(struct BattleUnit *bu) {
  int effWt = GetItemWeight(bu->weaponBefore);

  effWt -= bu->unit.conBonus;

  if (effWt < 0) {
    effWt = 0;
  }

  bu->battleSpeed = bu->unit.spd - effWt;
}

void computeBattleUnitAvoidRateUnfloored(struct BattleUnit *bu) {
  bu->battleAvoidRate = (bu->battleSpeed * 2) + bu->terrainAvoid + bu->unit.lck;
}

void defaultPopulateBattleStatGetters(struct BattleStatGetters *out) {
  out->computeAttack = ComputeBattleUnitAttack;
  out->computeDefense = ComputeBattleUnitDefense;
  out->computeSpeed = computeBattleUnitSpeedUnfloored;
  out->computeHit = ComputeBattleUnitHitRate;
  out->computeAvoid = computeBattleUnitAvoidRateUnfloored;
  out->computeCrit = ComputeBattleUnitCritRate;
  out->computeDodge = ComputeBattleUnitDodgeRate;
  out->computeSupportBonuses = ComputeBattleUnitSupportBonuses;
  out->computeWeaponRankBonuses = ComputeBattleUnitWeaponRankBonuses;
  out->computeStatusBonuses = ComputeBattleUnitStatusBonuses;
}

void initializeBonuses(struct InCombatBonuses *out) {
  out->attackMod = 0;
  out->defenseMod = 0;
  out->speedMod = 0;
  out->hitMod = 0;
  out->avoMod = 0;
  out->critMod = 0;
  out->dodgeMod = 0;
}

void applyCombatBonuses(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods
) {
  bu->battleAttack += mods->attackMod;
  opponent->battleDefense += mods->defenseMod;
  bu->battleSpeed += mods->speedMod;
  bu->battleHitRate += mods->hitMod;
  bu->battleAvoidRate += mods->avoMod;
  bu->battleCritRate += mods->critMod;
  bu->battleDodgeRate += mods->dodgeMod;
}

void ComputeBattleUnitStats(struct BattleUnit *bu, struct BattleUnit *opponent) {
  struct InCombatBonuses mods;
  initializeBonuses(&mods);
  populateBaseStats(bu, opponent);
  populateCombatBonuses(bu, opponent, &mods);
  applyCombatBonuses(bu, opponent, &mods);

  if (bu->battleSpeed < 0) {
    bu->battleSpeed = 0;
  }
  if (bu->battleAvoidRate < 0) {
    bu->battleAvoidRate = 0;
  }
}

void applyRoundResult(
    struct BattleUnit *attacker, struct BattleUnit *defender, struct RoundResult *attrs
) {
  gBattleStats.damage = 0;

  if (!attrs->didAttackHit) {
    gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_MISS;
    return;
  }

  if (attrs->didAttackerProcSkill) {
    gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_ATTACKER_SKILL;
  }

  if (attrs->didDefenderProcSkill) {
    gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_DEFENDER_SKILL;
  }

  if (attrs->didAttackCrit) {
    gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_CRIT;
  }

  gBattleStats.damage = attrs->finalDamage;

  if (gBattleStats.damage > BATTLE_MAX_DAMAGE) {
    gBattleStats.damage = BATTLE_MAX_DAMAGE;
  }

  if (gBattleStats.damage < 0) {
    gBattleStats.damage = 0;
  }

  BattleCheckPetrify(attacker, defender);

  if (gBattleStats.damage != 0) {
    attacker->nonZeroDamage = TRUE;
  }
}

void initRoundResult(struct RoundResult *out) {
  out->finalDamage = 0;
  out->didAttackHit = false;
  out->didAttackCrit = false;
  out->didAttackerProcSkill = false;
  out->didDefenderProcSkill = false;
}

void defaultPopulateRoundResult(
    struct BattleUnit *attacker, struct BattleUnit *defender, struct RoundResult *out
) {
  if (!BattleRoll2RN(gBattleStats.hitRate, TRUE)) {
    out->didAttackHit = false;
    return;
  }

  out->didAttackHit = true;

  out->finalDamage = gBattleStats.attack - gBattleStats.defense;

  if (BattleRoll1RN(gBattleStats.critRate, FALSE)) {
    out->didAttackCrit = true;
    out->finalDamage *= 3;
  }
}

void BattleGenerateHitAttributes(
    struct BattleUnit *attacker, struct BattleUnit *defender
) {
  struct RoundResult battleResult;
  initRoundResult(&battleResult);
  populateRoundResult(attacker, defender, &battleResult);
  applyRoundResult(attacker, defender, &battleResult);
}
