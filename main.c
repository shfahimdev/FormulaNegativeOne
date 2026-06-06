#include <stdlib.h>
#include <math.h>
#include <linux/input.h>
#include "keyhold.h"
#include "object.h"
#include "physics.h"
#include "render.h"

int main() {
  Object *car = NULL;
  init_object(&car);
  
  keyhold_start();

  float fps          = 60;
  float dt           = 1.0f / fps;
  float gravity      = 9.8f;
  float drive_force  = 170000.0f;

  render_init(900, 900, 60);

  while (!render_should_close()) {
    float fx = 0, fz = 0;
    car->ax = 0; car->ay = 0; car->az = 0;

    KeyState s = keyhold_get();
    if (s.held > 0 && s.key == 32) fx += drive_force;
    if (s.held > 0 && s.key == 30) fx -= drive_force;
    if (s.held > 0 && s.key == 31) fz -= drive_force;
    if (s.held > 0 && s.key == 17) fz += drive_force;

    apply_force(car, fx, 0, fz);
    apply_friction(car, gravity, dt);
    integrate(car, dt);

    float speed = sqrtf(car->vx*car->vx + car->vz*car->vz);
    render_frame(car);
  }
  render_close();
}
