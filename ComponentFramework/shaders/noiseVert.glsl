#version 460

layout (location = 0 ) in vec4 vVertex;
layout (location = 1 ) in vec4 vNormal;

layout ( location = 0 ) out vec3 vertNormal;
layout ( location = 1 ) out vec3 vertDir;

layout( location = 0 ) uniform mat4 projectionMatrix;
layout( location = 1 ) uniform mat4 viewMatrix;
layout( location = 2 ) uniform mat4 modelMatrix;
layout( location = 3 ) uniform mat3 normalMatrix;
layout( location = 4 ) uniform vec3 offset;

uniform sampler3D noiseTexture;



void main(){

vertNormal = normalMatrix * vNormal.xyz; //rotate normal to the right direction

vec3 vertPos = vec3(modelMatrix * vVertex);//vertex pos from origin
vertDir = normalize(vertPos);
vec3 vertex = vec3(vVertex);

vec4 noiseVec = texture(noiseTexture, (vertex * 0.4) + (0.25 * offset));
gl_Position = projectionMatrix * viewMatrix * modelMatrix * (vVertex + noiseVec);

}