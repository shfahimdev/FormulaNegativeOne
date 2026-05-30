#include <stdlib.h>
#include "object.h"

void init_object(Object **ball) {
  *ball = malloc(sizeof(Object));
  (*ball)->x = 0;
  (*ball)->y = 0;
  (*ball)->z = 0;
  (*ball)->vx = 0;
  (*ball)->vy = 0;
  (*ball)->vz = 0;
  (*ball)->ax = 0;
  (*ball)->ay = 0;
  (*ball)->az = 0;
  (*ball)->mass = 775;
}
