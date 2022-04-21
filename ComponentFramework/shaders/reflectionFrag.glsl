#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 vertNormal;//Direction of the normal 
layout(location = 1) in vec3 vertDir;
uniform samplerCube skybox;
layout(location = 0) out vec4 fragColor;//output color

void main() {
		vec3 reflection = normalize(reflect(vertDir, vertNormal));
		fragColor =  texture(skybox, reflection);	

	//fragColor = vec4(1,0,0,0);
}