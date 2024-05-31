#ifndef MICROSKILLSYS_COVERT_H
#define MICROSKILLSYS_COVERT_H

#include "bmunit.h"
#include "microskillsys/battle_simple.h"
#include "microskillsys/battleunit_calc.h"

bool hasCovert(struct Unit *unit);
void applyCovert(struct BattleStatGetters *getters);

#endif
