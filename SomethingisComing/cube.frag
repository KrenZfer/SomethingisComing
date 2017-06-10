#version 330 core

in vec3 ourColor;
in vec3 lightColor;

void main(){
	gl_FragColor = vec4(lightColor * ourColor, 1.0);
}