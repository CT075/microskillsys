#include "bmunit.h"
#include "constants/classes.h"

#include "NoGuard.h"

// CR cam: This is another skill that is fairly awkward to express under the
// existing interface, but it's less obvious to me how to extend the interface
// to allow this.

bool hasNoGuard(struct Unit *unit) { return UNIT_CLASS_ID(unit) == CLASS_WARRIOR; }
