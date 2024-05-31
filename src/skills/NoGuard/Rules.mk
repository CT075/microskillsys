sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

EVENTS_$(d) := $(d)/NoGuard.lyn.event

EVENTS := $(EVENTS) $(EVENTS_$(d))

d := $(dirstack_$(sp))
sp := $(basename $(sp))

