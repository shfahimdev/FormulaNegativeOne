#ifndef OBJECT_H
#define OBJECT_H

typedef struct {
  float x, y, z;
  float vx, vy, vz;
  float ax, ay, az;
  float mass;
} Object;

void init_object(Object **ball);

#endif
