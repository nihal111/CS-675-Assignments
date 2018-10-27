#version 330

in vec4 color;
in vec2 tex;

uniform sampler2D texture;
uniform int useTexture;

out vec4 frag_color;

void main () 
{
  if (useTexture == 0) {
    frag_color = color;
  } else {
    frag_color = texture2D(texture, tex);	
  }
}
