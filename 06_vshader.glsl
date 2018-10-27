#version 330

in vec4 vPosition;
in vec2 texCoord;

out vec2 tex;
uniform mat4 uModelViewMatrix;

void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  tex = texCoord;
}
