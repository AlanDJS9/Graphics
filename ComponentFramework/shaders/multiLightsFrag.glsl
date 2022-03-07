#version 450
#extension GL_ARB_separate_shader_objects : enable


layout(location = 0) in vec3 vertNormal;
layout(location = 1) in vec3 lightDirA;
layout(location = 2) in vec3 eyeDir; 
layout(location = 3) in vec2 texCoord; 
layout(location = 4) in vec3 lightDirB;


uniform sampler2D myTexture;
layout(location = 0) out vec4 fragColor;

void main() {
	
	vec4 kdA = vec4(0.7,0.7,0.7,0.0); //Deffiuse color
	vec4 kdB = vec4(0.8,0.0,0.0,0.0); //Deffiuse color

	vec4 ka = 0.1 * kdA;	//Ambient color
	vec4 ks = 0.7*kdA; //Specular color

	vec4 textureColor = texture(myTexture, texCoord);

    float diffA = max(dot(vertNormal, lightDirA), 0.0);  //Amount of diffuse
	float diffB = max(dot(vertNormal, lightDirB), 0.0);  //Amount of diffuse

	/// Reflection is based incedent which means a vector from the light source
	/// not the direction to the light source

	vec3 reflectionA = normalize(reflect(-lightDirA, vertNormal));
	vec3 reflectionB = normalize(reflect(-lightDirB, vertNormal));

	float specA = max(dot(eyeDir, reflectionA), 0.0);
	float specB = max(dot(eyeDir, reflectionB), 0.0);

	specA = pow(specA,14.0);
	specB = pow(specB,14.0);
				
	fragColor =  ka + (textureColor * kdA * diffA) + (ks * (specA)) + (textureColor * kdB * diffB) + (ks * (specB));	
}