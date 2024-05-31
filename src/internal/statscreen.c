#include "global.h"

#include "bmbattle.h"
#include "bmreliance.h"
#include "hardware.h"
#include "icon.h"
#include "statscreen.h"

#include "constants.h"
#include "microskillsys/constants.h"
#include "microskillsys/frontend.h"
#include "microskillsys/skills.h"

#include "ram_structures.h"

#define gUiTmScratchA ((u16 *)UI_SCRATCH_A_ADDR)

void drawSkillIcon(u16 *BgOut, int IconIndex, int OamPalBase);
void clearSkillIcons();

extern const u8 SkillIconTileGraphic[];

inline void displaySkills(void) {
  struct Unit *unit = gStatScreen.unit;
  int icons[MAX_SKILLS_POSSIBLE];

  for (int i = 0; i < MAX_SKILLS_POSSIBLE; i++) {
    icons[i] = -1;
  }

  clearSkillIcons();
  populateSkillIconList(unit, icons);

  for (int i = 0; i < MAX_SKILLS_POSSIBLE; i++) {
    if (icons[i] == -1) {
      return;
    }

    int idx = i + 1;

    drawSkillIcon(
        gUiTmScratchA + TILEMAP_INDEX(2 * idx, 14), icons[i],
        TILEREF(0, STATSCREEN_BGPAL_EXTICONS)
    );
  }
}

void DisplayBwl(void) {
  initSkillDisplay(gStatScreen.unit);
  displaySkills();
}

void redirectSkill(struct HelpBoxProc *proc) {
  struct Unit *unit = gStatScreen.unit;

  if (getNthSkillText(unit, 0) == -1) {
    proc->info = &sHelpInfo_Ss0Res;
  }

  if (getNthSkillText(unit, proc->info->mid) == -1) {
    TryRelocateHbLeft(proc);
  }
}

void populateSkill(struct HelpBoxProc *proc) {
  struct Unit *unit = gStatScreen.unit;

  proc->mid = getNthSkillText(unit, proc->info->mid);
}

const struct HelpBoxInfo sHelpInfo_Skill0;
const struct HelpBoxInfo sHelpInfo_Skill1;
const struct HelpBoxInfo sHelpInfo_Skill2;
const struct HelpBoxInfo sHelpInfo_Skill3;
const struct HelpBoxInfo sHelpInfo_Skill4;

const struct HelpBoxInfo sHelpInfo_Skill0 = {
  &sHelpInfo_Ss0Res, NULL,           NULL, &sHelpInfo_Skill1, 0x6C, 0x80, 0,
  &redirectSkill,    &populateSkill,
};

const struct HelpBoxInfo sHelpInfo_Skill1 = {
  &sHelpInfo_Ss0Res,
  NULL,
  &sHelpInfo_Skill0,
  &sHelpInfo_Skill2,
  0x7C,
  0x80,
  1,
  &redirectSkill,
  &populateSkill,
};

const struct HelpBoxInfo sHelpInfo_Skill2 = {
  &sHelpInfo_Ss0Res,
  NULL,
  &sHelpInfo_Skill1,
  &sHelpInfo_Skill3,
  0x8C,
  0x80,
  2,
  &redirectSkill,
  &populateSkill,
};

const struct HelpBoxInfo sHelpInfo_Skill3 = {
  &sHelpInfo_Ss0Res,
  NULL,
  &sHelpInfo_Skill2,
  &sHelpInfo_Skill4,
  0x9C,
  0x80,
  3,
  &redirectSkill,
  &populateSkill,
};

const struct HelpBoxInfo sHelpInfo_Skill4 = {
  &sHelpInfo_Ss0Res, NULL,           &sHelpInfo_Skill3, NULL, 0xAC, 0x80, 4,
  &redirectSkill,    &populateSkill,
};

// It is very annoying to need to reproduce all this manually. We could do the
// l33t thing and add a hook to replace the single pointer to `DrawnIconLookupTable`,
// but this is clearer

void clearSkillIcons() {
  CpuFill16(0, skillIconLookupTable, sizeof(struct IconStruct[MAX_SKILLS_POSSIBLE]));
  CpuFill16(0, skillIconGFXIDLookupTable, 0x20);
}

int getSkillIconGfxTileIndex(int idx) { return 0x300 - idx * 4; }

int getSkillIconGfxIndex(int Index) {
  int i;
  for (i = 0; i < MAX_SKILLS_POSSIBLE; i++) {
    if (skillIconGFXIDLookupTable[i] == 0) {
      skillIconGFXIDLookupTable[i] = Index + 1;
      return i;
    }
  }
  return -1;
}

u16 getSkillIconTileIndex(int Index) {
  if (skillIconLookupTable[Index].Index != 0) {
    if (skillIconLookupTable[Index].References < 0xFF) {
      skillIconLookupTable[Index].References++;
    }
  }
  else {
    skillIconLookupTable[Index].References++;
    skillIconLookupTable[Index].Index = getSkillIconGfxIndex(Index) + 1;

    RegisterDataMove(
        SkillIconTileGraphic + (Index * 0x80),
        (void *)(VRAM + (0x1FFE0 & (VRAM + 0x20 * getSkillIconGfxTileIndex(
                                                      skillIconLookupTable[Index].Index
                                                  )))),
        0x80
    );
  }
  return getSkillIconGfxTileIndex(skillIconLookupTable[Index].Index);
}

void drawSkillIcon(u16 *BgOut, int IconIndex, int OamPalBase) {
  if (IconIndex < 0) {
    BgOut[0] = 0;
    BgOut[1] = 0;
    BgOut[32] = 0;
    BgOut[33] = 0;
  }
  else {
    u16 Tile = getSkillIconTileIndex(IconIndex) + OamPalBase;

    BgOut[0] = Tile++;
    BgOut[1] = Tile++;
    BgOut[32] = Tile++;
    BgOut[33] = Tile;
  }
}
