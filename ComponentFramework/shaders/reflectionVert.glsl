#version 450
#extension GL_ARB_separate_shader_objects : enable

//Atributes in = in coming info into the GPU
layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec3 vNormal;

                     //uniforms = values that are not going to change = const  
layout(location = 0) uniform mat4 projectionMatrix;
layout(location = 1) uniform mat4 viewMatrix;
layout(location = 2) uniform mat4 modelMatrix;


layout(location = 0) out vec3 vertNormal; 
layout (location = 1) out vec3  vertDir;

void main() {
// 
mat4 pureRotationMatrix = transpose(inverse(modelMatrix));
mat3 normalMatrix = mat3(pureRotationMatrix);
vertNormal = normalMatrix * vNormal; //Might point to the right direction
vertNormal = normalize(vertNormal); //We do it just to be sure thats 1

 vec3 vertPos = vec3(viewMatrix * modelMatrix * vVertex);
    //Position normalized = direction
  vertDir = normalize(vertPos);

//The camera doesnt move, everything orientates to the view
                                                 //translate rotate or scale matrix - Manipulates de model    
                                                                //Vertex of the model                                                 
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vVertex;
                                    //where the "camera is" / perspective values on x,y,z
}