#include "global.h"

#include "bmbattle.h"
#include "bmitem.h"
#include "bmunit.h"

#include "microskillsys/buffs.h"

int GetUnitPower(struct Unit *unit) {
  return unit->pow + GetItemPowBonus((u16)GetUnitEquippedWeapon(unit)) +
         unitPowBuff(unit);
}

int GetUnitSkill(struct Unit *unit) {
  u16 item = GetUnitEquippedWeapon(unit);

  if (unit->state & US_RESCUING)
    return unit->skl / 2 + GetItemSklBonus(item);

  return unit->skl + GetItemSklBonus(item) + unitSklBuff(unit);
}

int GetUnitSpeed(struct Unit *unit) {
  u16 item = GetUnitEquippedWeapon(unit);

  if (unit->state & US_RESCUING)
    return unit->spd / 2 + GetItemSpdBonus(item);

  return unit->spd + GetItemSpdBonus(item) + unitSpdBuff(unit);
}

int GetUnitDefense(struct Unit *unit) {
  return unit->def + GetItemDefBonus((u16)GetUnitEquippedWeapon(unit)) +
         unitDefBuff(unit);
}

int GetUnitResistance(struct Unit *unit) {
  return unit->res + GetItemResBonus((u16)GetUnitEquippedWeapon(unit)) +
         unit->barrierDuration + unitResBuff(unit);
}

int GetUnitLuck(struct Unit *unit) {
  return unit->lck + GetItemLckBonus((u16)GetUnitEquippedWeapon(unit)) +
         unitLckBuff(unit);
}
