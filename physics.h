#ifndef PHYSICS_H
#define PHYSICS_H
#include "object.h"

void integrate(Object *ball, float dt);
void apply_force(Object *ball ,float fx, float fy, float fz);
void apply_friction(Object *ball ,float gravity, float dt);

#endif
