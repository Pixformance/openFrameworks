#version 150
#define KERNEL_SIZE 9

uniform sampler2DRect backbuffer;   // recive the previus velocity texture
uniform sampler2DRect posData;      // recive the position texture

uniform vec2  screen;

uniform float timestep;
in vec2 texCoordVarying;
out vec4 fragColor;
    
void main(void){
    vec2 st = texCoordVarying;    // gets the position of the pixel that it´s dealing with...
    
    vec2 pos = texture( posData, st).xy;      // ... for gettinh the position data 
    vec2 vel = texture( backbuffer, st ).xy;  // and the velocity
        
    // Calculates what´s going to be the next position without updating it.
    // Just to see if it collide with the borders of the FBO texture
    //
    vec2 nextPos = pos; 
    nextPos += vel * timestep;
        
        
    // If it´s going to collide change the velocity course
    //
    if ( nextPos.x < 0.0)
        vel.x = 0.5 * abs(vel.x);
        
    if ( nextPos.x > 1.0)
        vel.x = -0.5 * abs(vel.x);
        
    if (nextPos.y < 0.0)
        vel.y = 0.5 * abs(vel.y);
    
    if ( nextPos.y > 1.0)
        vel.y = -0.5 * abs(vel.y);
    
        
    fragColor = vec4(vel.x,vel.y,0.0,1.0);   // Then save the vel data into the velocity FBO
}