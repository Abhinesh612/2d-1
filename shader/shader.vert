#version 460 core
layout (location = 0) a_pos;

void main() {
	gl_Position = vec4(a_pos, 1.0);
}
