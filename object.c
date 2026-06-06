#include <stdlib.h>
#include "object.h"

void init_object(Object **obj) {
  *obj = malloc(sizeof(Object));
  (*obj)->x = 0 ; (*obj)->y = 0 ; (*obj)->z = 0;
  (*obj)->vx = 0; (*obj)->vy = 0; (*obj)->vz = 0;
  (*obj)->ax = 0; (*obj)->ay = 0; (*obj)->az = 0;
  (*obj)->mass = 70.0f;
  (*obj)->friction_coefficient = 200.0f;
}
