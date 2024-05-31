![microskillsys exists because cam needed it](microskillsys.png)

(thanks to Black Mage for the perfect summary of how this project came to be!)

## What is this?

**microskillsys** is an alternative skill system implementation for FE8. It was
initially written and designed for my [CELICA](https://github.com/CT075/celica-2024)
entry, but has since been reworked to be applicable more generally.

This project has two primary design goals:

- To provide a streamlined, uniform interface for writing new skills
- To be as compatible as possible with both existing and future engine mods by
  minimizing dependencies and hooks into vanilla code.

In comparison to the existing [FE8 Skill System](https://github.com/FireEmblemUniverse/SkillSystem_FE8),
(henceforth just "SkillSystem") which attempts to provide a "batteries included"
experience with many skills and extensions built-in, this project seeks instead
to expose a series of building blocks for users to craft their own skill system.

This project is intended for **expert users** proficient with make-based
EA buildfiles, specifically writing C functions to be linked in with `lyn`. By
design, this project comes with very few defaults, and an unmodified install
should not change vanilla behavior whatsoever (if you discover this not to be
the case, please file a bug report!).

## Why should I use microskillsys over SkillSystem?

- You don't need all of the machinery included with SkillSystem 1.x and would
  rather only include functionality that is strictly necessary.
- You intend to change some internals of the skill system itself (for example,
  using a custom implementation of `SkillTester` in SkillSystem 1.x).
- You would like to use another engine hack that is incompatible with SkillSystem
  1.x. Note that this project does not guarantee compatibility with other mods,
  but this project's simpler codebase should make it simpler to re-implement
  those mods in a compatible way.

## Why *shouldn't* I use microskillsys?

- You are a beginner to FE8 engine hacking and intend to use many of the features
  or skills included with the default SkillSystem 1.x.
- You have an existing project using SkillSystem 1.x. There is no easy process
  for porting such a project to use this backend instead.
- You intend to have many "higher-order" skills that affect other skills, such
  as Nihil (from Radiant Dawn) or Rightful King (from Awakening). Due to the
  self-contained design of the skill interface (as opposed to SkillSystem's
  calc loops), implementing such skills is unwieldy but not impossible.
