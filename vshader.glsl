#version 330

in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;
in vec2 texCoord;

uniform mat4 uModelViewMatrix;
uniform mat3 normalMatrix;
uniform int useTexture;

out vec4 color;
out vec2 tex;
out vec4 eye;
out vec3 normal;


void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  normal = (normalMatrix * normalize(vNormal)); 
  eye = - (uModelViewMatrix * gl_Position); 
  if (useTexture ==0) {
    color = vColor;
  } else {
    tex = texCoord;
  }
}
