#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <linux/input.h>
#include "keyhold.h"
#include "object.h"
#include "physics.h"

int main() {
  Object *ball = NULL;
  init_object(&ball);

  keyhold_start();
  float fps = 60;
  float dt = 1.0f / fps;
  float fx = 0;
  float fy = 0;
  float fz = 0;
  float force_per_second = 17000.0f;

  struct timespec ts = { 0, 16666667L }; // ~60fps

  while (1) {
    KeyState s = keyhold_get();
      if (s.held > 0 && s.key == 17) {
        fx += force_per_second * dt;
        printf("Current Fx = %.3f\n", fx);
      } 

      if (s.held > 0 && s.key == 31) {
        fx -= force_per_second * dt;
        printf("Current Fx = %.3f\n", fx);
      }
      if (s.held > 0 && s.key == 30) {
        fz -= force_per_second * dt;
        printf("Current Fz = %.3f\n", fz);
      }
      if (s.held > 0 && s.key == 32) {
        fz += force_per_second * dt;
        printf("Current Fz = %.3f\n", fz);
      }
      if (fx > 0 || fx < 0 || fz > 0 || fz < 0) {
        ball->ax = 0;
        ball->ay = 0;
        ball->az = 0;
        apply_force(ball, fx, fy, fz);
        integrate(ball, dt);
        printf("(x,y,z) = (%f, %f, %f)\n", ball->x, ball->y, ball->z);
      } else {
        printf("The car is stationary\n");
      }
      nanosleep(&ts, NULL);
    }
}
