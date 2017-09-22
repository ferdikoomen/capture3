#version 410 core

in vec4 vertexPosition;
in vec4 vertexColor;

uniform mat4 matrix;

out vec4 color;

void main()
{
	color = vertexColor;
	gl_Position = matrix * vertexPosition;
}