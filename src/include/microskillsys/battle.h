#ifndef MICROSKILLSYS_BATTLE_H
#define MICROSKILLSYS_BATTLE_H

#include "bmbattle.h"
#include "bmunit.h"
#include "global.h"

// CR cam: clean this up before release

#define MAX_BATTLE_ROUNDS 8

// Battle system primitives

enum BattlePosition {
  InitiatorTurn = 1,
  TargetTurn = 2,
  BattleOver = 0,
};

struct BattleRound {
  enum BattlePosition turn : 4;
  u32 count : 4;
};

void clearRoundOrder();
void defaultPopulateRoundOrder();

// Pre-battle helpers

// CR cam: Move these to [battle_simple.h]?
struct InCombatBonuses {
  // Flat damage applied to final attack
  u8 attackMod;
  // Flat damage applied to final defense
  u8 defenseMod;
  u8 speedMod;
  u8 hitMod;
  u8 avoMod;
  u8 critMod;
  u8 dodgeMod;
};

void vanillaPopulatePreBattleMods(
    struct BattleUnit *unit, struct BattleUnit *opponent, struct InCombatBonuses *out
);
// CR-soon cam: Do we need to expose all of these?
void computeBattleUnitAttackBasic(
    struct BattleUnit *unit, struct BattleUnit *opponent,
    struct InCombatBonuses *mods
);
void computeBattleUnitDefenseBasic(
    struct BattleUnit *unit, struct BattleUnit *opponent,
    struct InCombatBonuses *mods
);
void computeBattleUnitSpeedBasic(
    struct BattleUnit *bu, struct InCombatBonuses *mods
);
void computeBattleUnitHitRateBasic(
    struct BattleUnit *bu, struct InCombatBonuses *mods
);
void computeBattleUnitAvoidRateBasic(
    struct BattleUnit *bu, struct InCombatBonuses *mods
);
void computeBattleUnitCritRateBasic(
    struct BattleUnit *bu, struct InCombatBonuses *mods
);
void computeBattleUnitDodgeRateBasic(
    struct BattleUnit *bu, struct InCombatBonuses *mods
);
void computeBattleUnitStatsBasic(
    struct BattleUnit *unit, struct BattleUnit *opponent,
    struct InCombatBonuses *mods
);
void defaultBattleUnitStats(struct BattleUnit *unit, struct BattleUnit *opponent);

void applyCombatBonuses(
    struct BattleUnit *bu, struct BattleUnit *opponent, struct InCombatBonuses *mods);

// final battle mods

enum {
  BATTLE_HIT_ATTR_ATTACKER_SKILL = BATTLE_HIT_ATTR_SURESHOT,
  BATTLE_HIT_ATTR_DEFENDER_SKILL = BATTLE_HIT_ATTR_GREATSHLD,
};

struct RoundResult {
  short finalDamage;
  bool didAttackHit;
  bool didAttackCrit;
  // For visual effect only
  bool didAttackerProcSkill;
  // For visual effect only
  bool didDefenderProcSkill;
};

void defaultPopulateRoundResult(
    struct BattleUnit *attacker, struct BattleUnit *defender, struct RoundResult *out
);

// Re-exports of vanilla functions for some reason or other

void computeBattleUnitSpeedUnfloored(struct BattleUnit *bu);
void computeBattleUnitHitRateUnfloored(struct BattleUnit *bu);
void computeBattleUnitAvoidRateUnfloored(struct BattleUnit *bu);

#endif
