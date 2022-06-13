#version 460

in vec3 vertNormal;
in vec3 vertDir;
out vec4 fragColor;
uniform samplerCube skyboxTexture;

//Fancy new code

vec4 reflection();
vec4 refraction();
vec4 bothCombined();

void main(){
	fragColor = bothCombined();
	//fragColor = refraction();
	//fragColor = reflection();
}

vec4 reflection(){
	vec3 vReflection = reflect(vertDir, vertNormal);
	vReflection.x *= -1.0;
	return texture(skyboxTexture, vReflection);
}

vec4 refraction(){
	vec3 vRefraction = refract(-vertDir, vertNormal, 1.0/1.52);
	return texture(skyboxTexture, vRefraction);
}

vec4 bothCombined(){
	vec3 vRefraction = refract(-vertDir, vertNormal, 1.0/1.52);

	vec3 vReflection = reflect(vertDir, vertNormal);
	vReflection.x *= -1.0;

	vec3 both = mix(vReflection, vRefraction, dot(vertNormal, -vertDir));
	return texture(skyboxTexture, both);
}