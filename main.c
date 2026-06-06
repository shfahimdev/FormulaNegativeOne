#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <linux/input.h>
#include "keyhold.h"
#include "object.h"
#include "physics.h"

int main() {
  Object *car = NULL;
  init_object(&car);
  
  keyhold_start();

  float fps          = 60;
  float dt           = 1.0f / fps;
  float gravity      = 9.8f;
  float drive_force  = 170000.0f;

  struct timespec ts = { 0, (long)(dt * 1e9f) }; // ~60fps

  while (1) {
    float fx = 0, fz = 0;
    car->ax = 0; car->ay = 0; car->az = 0;

    KeyState s = keyhold_get();
    if (s.held > 0 && s.key == 17) fx += drive_force;
    if (s.held > 0 && s.key == 31) fx -= drive_force;
    if (s.held > 0 && s.key == 30) fz -= drive_force;
    if (s.held > 0 && s.key == 32) fz += drive_force;

    apply_force(car, fx, 0, fz);
    apply_friction(car, gravity, dt);
    integrate(car, dt);

    float speed = sqrtf(car->vx*car->vx + car->vz*car->vz);
    printf("pos=(%.2f, %.2f)  speed=%.3f m/s\n", car->x, car->z, speed);

    nanosleep(&ts, NULL);
  }
}
