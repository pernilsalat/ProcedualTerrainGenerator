#version 430 

in vec3 position;

uniform mat4 view;
uniform mat4 projection;

void main(void) {
	gl_Position = projection * view *  vec4(position, 1);
}