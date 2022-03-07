#version 450
#extension GL_ARB_separate_shader_objects : enable

//Atributes in = in coming info into the GPU
layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 uvCoord;

                     //uniforms = values that are not going to change = const  
layout(location = 0) uniform mat4 projectionMatrix;
layout(location = 1) uniform mat4 viewMatrix;
layout(location = 2) uniform mat4 modelMatrix;
 layout(location = 3) uniform vec3 lightPos;

layout(location = 0) out vec3 vertNormal;
layout(location = 1) out vec3 lightDir;
layout(location = 2) out vec3 eyeDir; 
layout(location = 3) out vec2 texCoord; 

void main() {
texCoord = uvCoord;
texCoord.y *= -1.0; //shaders are f
mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
vertNormal = normalize(normalMatrix * vNormal);
    vec3 vertPos = vec3(viewMatrix * modelMatrix * vVertex);
    //Position normalized = direction
    vec3 vertDir = normalize(vertPos);
    eyeDir = -vertDir;
    lightDir = normalize((lightPos) - vertPos); 
//The camera doesnt move, everything orientates to the view
                                                 //translate rotate or scale matrix - Manipulates de model    
                                                                //Vertex of the model                                                 
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vVertex;
                                    //where the "camera is" / perspective values on x,y,z
}