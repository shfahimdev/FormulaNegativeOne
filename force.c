#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float x, y, z;
  float vx, vy, vz;
  float ax, ay, az;
  float mass;
} Object;

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
  (*ball)->mass = 1;
}

int main() {
  Object *ball = NULL;
  init_object(&ball);

  float duration = 100000000;
  float fps = 60;
  float dt = 1.0f / fps;

  int j = 0;

  for (float i = 0; i <= duration; i += dt) {
    ball->ax = 0;
    ball->ay = 0;
    ball->az = 0;
    apply_force(ball, 45, 0, 0);
    apply_force(ball, 0, 87, 0);
    apply_force(ball, 0, 0, 100);
    integrate(ball, dt);
    printf("Step - %d ---> (x,y,z) = (%f, %f, %f) @ time = %f\n", j, ball->x, ball->y, ball->z, i);
    j++;
  }


  free(ball);
  ball = NULL;
  return 0;
}
