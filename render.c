#include "raylib.h"
#include "render.h"
#include <math.h>

#define SCALE 2.0f         
#define TRAIL_MAX 512

static Vector2 trail[TRAIL_MAX];
static int trail_head = 0, trail_count = 0;

static int SW, SH;

void render_init(int w, int h, int fps) {
    SW = w; SH = h;
    InitWindow(w, h, "physics viz");
    SetTargetFPS(fps);
}

void render_frame(Object *car) {
    Vector2 pos = {
        SW/2 + car->x * SCALE,
        SH/2 - car->z * SCALE
    };

    // store trail
    trail[trail_head] = pos;
    trail_head = (trail_head + 1) % TRAIL_MAX;
    if (trail_count < TRAIL_MAX) trail_count++;

    BeginDrawing();
    ClearBackground(BLACK);

    DrawLine(0, SH/2, SW, SH/2, DARKGRAY);   // X
    DrawLine(SW/2, 0, SW/2, SH, DARKGRAY);   // Z

    // trail
    for (int i = 0; i < trail_count - 1; i++) {
        int a = (trail_head - trail_count + i + TRAIL_MAX) % TRAIL_MAX;
        int b = (a + 1) % TRAIL_MAX;
        DrawLineV(trail[a], trail[b], GRAY);
    }

    DrawCircleV(pos, 6, RED);

    float speed = sqrtf(car->vx*car->vx + car->vz*car->vz);
    DrawText(TextFormat("pos=(%.1f, %.1f)  speed=%.2f m/s",
             car->x, car->z, speed), 10, 10, 18, WHITE);

    EndDrawing();
}

void render_close() { CloseWindow(); }
int render_should_close() { return WindowShouldClose(); }
