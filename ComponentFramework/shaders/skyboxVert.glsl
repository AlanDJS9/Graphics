#version 450
#extension GL_ARB_separate_shader_objects : enable

//Atributes in = in coming info into the GPU
layout(location = 0) in vec4 vVertex;


                     //uniforms = values that are not going to change = const  
layout(location = 0) uniform mat4 projectionMatrix;
layout(location = 1) uniform mat4 viewMatrix;


layout(location = 0) out vec3 texCoord; 

void main() {
texCoord = vec3(vVertex);
texCoord.x *= -1.0f;
//Only cool weird kids move
//texCoord = vVertex.xyz;
//The camera doesnt move, everything orientates to the view
                                                 //translate rotate or scale matrix - Manipulates de model    
                                                                //Vertex of the model                                                 
    gl_Position = projectionMatrix * viewMatrix  * vVertex;
                                    //where the "camera is" / perspective values on x,y,z
}