#include <stdbool.h>

#include "engine/types.h"
#include "engine/render/render.h"
#include "engine/render/render_internal.h"

Render_State state;
f32 color[4] = {0.08f, 0.1f, 0.1f, 1.f};
static bool quit = false;

int main() {
	render_window_set_title(&state, "MyGame");
	render_window_set_size(&state, 800, 600);
	render_shader_set_path(&state, "shader/shader.vert", "shader/shader.frag");

	render_init(&state);

	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
				default:
					break;
			}
		}
		render_begin(color);
		render_end();
	}

	return 0;
}
