#include <stdlib.h>

#include "render_internal.h"
#include "../util.h"
#include "../io/ios.h"

void render_window_create_window(Render_State* state) {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		ERROR_EXIT("ERROR::FAIELD TO INITAILZE SDL: %s\n", SDL_GetError());
	}

	SDL_Window* window = SDL_CreateWindow(state->render_window.title,
										  SDL_WINDOWPOS_CENTERED,
										  SDL_WINDOWPOS_CENTERED,
										  state->render_window.width,
										  state->render_window.height,
										  SDL_WINDOW_OPENGL);

	if (window == NULL) {
		ERROR_EXIT("ERROR::FAILED TO CREATE WINDOW: %s\n", SDL_GetError());
	}

	SDL_GL_CreateContext(window);

	state->render_window.window = window;

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		ERROR_EXIT("ERROR::FAIELD TO INITAILZE GLAD: %s\n", SDL_GetError());
	}

	printf("OpenGL Loaded\n");
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
}

void render_shader_create(Render_State* state) {
	u32 success;
	char log[512];

	char* file_vert = io_file_read(state->render_shader.shader_vertex);
	u32 shader_vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader_vertex, 1, (const char* const*)&file_vert, NULL);
	glCompileShader(shader_vertex);
	glGetShaderiv(shader_vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader_vertex, 512, NULL, log);
		ERROR_EXIT("ERROR::FAILED TO COMPILE VERTEX SHADER: %s : %s\n",
				   state->render_shader.shader_vertex,
				   log);
	}

	char* file_frag = io_file_read(state->render_shader.shader_fragment);
	u32 shader_fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader_fragment, 1, (const char* const*)&file_frag, NULL);
	glCompileShader(shader_fragment);
	glGetShaderiv(shader_fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader_fragment, 512, NULL, log);
		ERROR_EXIT("ERROR::FAILED TO COMPILE FRAGMENT SHADER: %s : %s\n",
				   state->render_shader.shader_fragment,
				   log);
	}

	u32 shader_program = glCreateProgram();
	glAttachShader(shader_program, shader_vertex);
	glAttachShader(shader_program, shader_fragment);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, log);
		ERROR_EXIT("ERROR::FAILED TO LINK SHADER: %s\n", log);
	}

	state->render_shader.shader_program = shader_program;

	free(file_vert);
	free(file_frag);

	glDeleteShader(shader_vertex);
	glDeleteShader(shader_fragment);
}

void render_shader_array_init(Render_State* state) {
	f32 vertices[] = {
		 0.5f,  0.5f, 0.f,
		 0.5f, -0.5f, 0.f,
		-0.5f, -0.5f, 0.f,
		-0.5f,  0.5f, 0.f,
	};
	u32 indices[] = {
		0, 1, 3,
		1, 2, 3,
	};

	glGenVertexArrays(1, &state->render_shader.vao);
	glGenBuffers(1, &state->render_shader.vbo);
	glGenBuffers(1, &state->render_shader.ebo);

	glBindVertexArray(state->render_shader.vao);
	glBindBuffer(GL_ARRAY_BUFFER, state->render_shader.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, state->render_shader.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}
