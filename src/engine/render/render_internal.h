#ifndef __RENDER_WINDOW_H
#define __RENDER_WINDOW_H

#include "render.h"

void render_window_set_title(Render_State* state, char* title);
void render_window_set_size(Render_State* state, u32 widht, u32 height);
void render_window_create_window(Render_State* state);

void render_shader_set_path(Render_State* state, char* path_vert, char* path_frag);
void render_shader_create(Render_State* state);

#endif // __RENDER_WINDOW_H
