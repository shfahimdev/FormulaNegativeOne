#ifndef KEYHOLD_H
#define KEYHOLD_H

typedef struct {
    int key;       // key code (e.g. KEY_W = 17)
    double held;   // seconds held, 0 if not holding
} KeyState;

void keyhold_start();
KeyState keyhold_get();

#endif
