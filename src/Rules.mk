sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

dir := $(d)/internal
include $(dir)/Rules.mk

dir := $(d)/skills
include $(dir)/Rules.mk

$(d)/frontend.o: $(RAM_STRUCTURES_H)

EVENTS_$(d) := $(d)/microskillsys.event $(d)/frontend.lyn.event

EVENTS := $(EVENTS) $(EVENTS_$(d))

# Cross-subdir rules
# CR cam: Really, we should be doing this with a script instead of in make

.SECONDEXPANSION:

$(shell mkdir -p $(d)/include/microskillsys/skills)
$(d)/include/microskillsys/skills/%.h: $(d)/skills/$$*/$$*.h
	cp $< $@

$(d)/include/microskillsys/skills.h: $(shell \
	cat $(d)/skills/skill_list.txt | \
	xargs -I '{}' python -c 'print("$(d)/include/microskillsys/skills/{}.h")')
$(d)/include/microskillsys/skills.h: $(d)/skills/skill_list.txt
	cat $< \
		| xargs -I '{}' python -c 'print("#include \"skills/{}.h\"")' \
		> $@

$(d)/include/microskillsys/icons.h: $(d)/skills/icons/installer.event
	sed -n '/^#define/p' $< > $@

# no idea why this needs to be done manually
$(d)/frontend.o: $(d)/include/microskillsys/icons.h

d := $(dirstack_$(sp))
sp := $(basename $(sp))
