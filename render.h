#pragma once
#include "object.h"

void render_init(int screen_w, int screen_h, int fps);
void render_frame(Object *car);  
void render_close();
int render_should_close(); 
