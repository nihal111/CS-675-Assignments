#version 330

in vec4 vPosition;
in vec4 vColor;
in vec2 texCoord;

uniform mat4 uModelViewMatrix;
uniform int useTexture;

out vec4 color;
out vec2 tex;

void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  if (useTexture ==0) {
    color = vColor;
  } else {
    tex = texCoord;
  }
}
