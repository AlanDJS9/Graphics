#version 460

layout (location = 0 ) in vec4 vVertex;
layout (location = 1 ) in vec4 vNormal;


out vec3 vertNormal;
out vec3 vertDir;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform float totalTime;

void main(){
vertNormal = normalMatrix * vNormal.xyz;
vec4 grow = vVertex * totalTime;
grow.w = 1.0;
gl_Position = projectionMatrix * viewMatrix * modelMatrix * (grow);
}