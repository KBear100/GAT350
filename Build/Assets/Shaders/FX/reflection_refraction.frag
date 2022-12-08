#version 430 core

in vec3 reflection_dir;
in vec3 refraction_dir;

out vec4 fcolor;

layout (binding = 0) uniform samplerCube cubemap;
uniform float interpolation = 0.1;

void main()
{
	vec3 reflect_color = texture(cubemap, reflection_dir).rgb;
	vec3 refract_color = texture(cubemap, refraction_dir).rgb;

	vec3 color = mix(reflect_color, refract_color, interpolation);

	fcolor = texture(cubemap, color);
}
