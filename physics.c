#include "object.h"
#include <math.h>

void apply_force(Object *obj, float fx, float fy, float fz) {
    obj->ax += fx / obj->mass;   
    obj->ay += fy / obj->mass;
    obj->az += fz / obj->mass;
}

void integrate(Object *obj, float dt) {
    obj->vx += obj->ax * dt;
    obj->vy += obj->ay * dt;
    obj->vz += obj->az * dt;

    obj->x += obj->vx * dt;
    obj->y += obj->vy * dt;
    obj->z += obj->vz * dt;
}

void apply_friction(Object *obj, float gravity, float dt) {
  float normalForce = obj->mass * gravity;
  float friction_magnitude = obj->friction_coefficient * normalForce;

  float speed = sqrtf(obj->vx * obj->vx + obj->vz * obj->vz);

  if (speed < 1e-4f) {
    obj->vx = 0;
    obj->vz = 0;
    return;
  }

  float decel = (friction_magnitude / obj->mass) * dt;
  if (decel > speed) decel = speed;
  obj->vx -= (obj->vx / speed) * decel;
  obj->vz -= (obj->vz / speed) * decel;
}
