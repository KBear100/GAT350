#version 430 core

in vec3 refraction_dir;

out vec4 fcolor;

layout (binding = 0) uniform samplerCube cubemap;

void main()
{
	fcolor = texture(cubemap, refraction_dir);
}
