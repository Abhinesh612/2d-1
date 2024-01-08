#include "render_internal.h"
#include "../util.h"

void render_window_set_title(Render_State* state, char* title) {
	state->render_window.title = title;
}

void render_window_set_size(Render_State* state, u32 width, u32 height) {
	state->render_window.width  = width;
	state->render_window.height = height;
}

void render_shader_set_path(Render_State* state, char* path_vert, char* path_frag) {
	state->render_shader.shader_vertex   = path_vert;
	state->render_shader.shader_fragment = path_frag;
}
