#include "object.h"

void integrate(Object *ball, float dt) {
  ball->vx += ball->ax * dt;
  ball->vy += ball->ay * dt;
  ball->vz += ball->az * dt;

  ball->x += ball->vx * dt;
  ball->y += ball->vy * dt;
  ball->z += ball->vz * dt;
};

void apply_force(Object *ball ,float fx, float fy, float fz) {
  ball->ax += fx / ball->mass;
  ball->ay += fy / ball->mass;
  ball->az += fz / ball->mass;
}
