// CR cam: come up with a better name for this

#ifndef MICROSKILLSYS_BATTLE_SIMPLE_H
#define MICROSKILLSYS_BATTLE_SIMPLE_H

#include "microskillsys/battle.h"

struct PrebattleActors {
  // We do not pass the full [BattleUnit]s, because they aren't fully populated
  // yet.
  struct Unit *unit;
  u16 unitWeapon;
  struct Unit *opponent;
  u16 opponentWeapon;
};

// CR cam: This is maybe not expressive enough (see Reckless)
struct SimplePreBattleSkillSpec {
  bool (*applies)(struct Unit *unit);
  void (*apply)(
      struct BattleUnit *attacker, struct BattleUnit *defender,
      struct InCombatBonuses *mods
  );
};

enum ProcSide { Attacker, Defender };

struct ProcSkillSpec {
  enum ProcSide side;
  bool (*canProc)(struct Unit *bu);
  int (*procRate)(struct BattleUnit *bu);
  void (*apply)(
      struct BattleUnit *attacker, struct BattleUnit *defender,
      struct RoundResult *result
  );
};

#endif
