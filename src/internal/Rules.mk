sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

$(d)/battle.o: $(RAM_STRUCTURES_H)

$(d)/statscreen.o: $(PARSE_DEFNS_H)

EVENTS_$(d) := $(d)/statscreen.lyn.event $(d)/battle.lyn.event $(d)/buffs.lyn.event

EVENTS := $(EVENTS) $(EVENTS_$(d))

d := $(dirstack_$(sp))
sp := $(basename $(sp))
