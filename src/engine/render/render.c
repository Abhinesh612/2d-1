#include <stdio.h>

#include "render.h"
#include "render_internal.h"
#include "../util.h"
#include "../io/ios.h"

static Render_State* state = NULL;

void render_init(Render_State* render_state) {
	state = render_state;
	render_window_create_window(state);
	render_shader_create(state);
	render_shader_array_init(state);
}

void render_begin(f32 color[4]) {
	glClearColor(color[0], color[1], color[2], color[3]);
	glClear(GL_COLOR_BUFFER_BIT);
}

void render_draw_quad() {
	glUseProgram(state->render_shader.shader_program);

	glBindVertexArray(state->render_shader.vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void render_end() {
	SDL_GL_SwapWindow(state->render_window.window);
}
