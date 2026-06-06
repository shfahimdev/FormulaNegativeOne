# FormulaNegativeOne

A from-scratch Formula 1 simulator written in C. No game engine... just raw physics, real math, and a long road ahead.

## What it does

Simulates a car on a 2D plane (X/Z) with real Newtonian physics: force application, Euler integration, and kinetic friction. Keyboard input is captured directly from the Linux input event system, so key-hold duration is tracked with microsecond precision.

## Project structure

```
main.c        — Game loop (~60fps), input polling, force application
object.c/h    — Rigid body struct (position, velocity, acceleration, mass, friction)
physics.c/h   — apply_force, integrate, apply_friction
keyhold.c/h   — Background pthread reading /dev/input for real-time key state
Makefile      — gcc build with -lm -lpthread
```

## Build & run

```bash
make
sudo ./formulanegativeone   # sudo needed for /dev/input access
```

> **Note:** The keyboard device is hardcoded to `/dev/input/event6` in `keyhold.c`. Change this to match your system (`cat /proc/bus/input/devices` to find yours).

## Controls

| Key | Action       |
|-----|--------------|
| W   | Accelerate forward |
| S   | Brake / reverse    |
| A   | Strafe left        |
| D   | Strafe right       |

## Current physics model

- Mass: 775 kg (close to real F1 spec)
- Drive force: 170,000 N
- Isotropic kinetic friction (μ = 0.6)
- Euler integration at 60Hz

## Roadmap

This is the foundation. The long-term goal is a realistic F1 simulator. Planned areas of work:

- Heading/orientation and steering
- Tire model with lateral vs longitudinal grip
- Engine torque curve and gear ratios
- Aerodynamic downforce
- Weight transfer under braking and acceleration
- RK4 or Verlet integration for accuracy at speed
- Rendering

---

*Started by Shahriar Fahim. Target: a full F1 simulator in 5–6 years.*
