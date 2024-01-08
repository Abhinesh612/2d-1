#ifndef __RENDER_H
#define __RENDER_H

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "../types.h"

typedef struct Render_Window {
	SDL_Window* window;
	char* title;
	u32 width;
	u32 height;
} Render_Window;

typedef struct Render_Shader {
	char* shader_vertex;
	char* shader_fragment;
	u32 shader_program;
	u32 vao;
	u32 vbo;
	u32 ebo;
} Render_Shader;

typedef struct Render_State {
	Render_Window render_window;
	Render_Shader render_shader;
} Render_State;

void render_init(Render_State* render_state);
void render_begin(f32 color[4]);
void render_draw_quad(void);
void render_end(void);

#endif // __RENDER_H
