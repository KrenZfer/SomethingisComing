#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 color;
uniform vec3 lightColorin;

out vec3 lightColor;
out vec3 ourColor;

void main(){
	gl_Position = projection * view * model * vec4(position, 1.0f);
	lightColor = lightColorin;
	ourColor = color;
}