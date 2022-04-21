#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 texCoord; 
uniform samplerCube skybox;
layout(location = 0) out vec4 fragColor;//output color

void main() {
	fragColor =  texture(skybox, texCoord);	
	//fragColor = vec4(1,0,0,0);
}