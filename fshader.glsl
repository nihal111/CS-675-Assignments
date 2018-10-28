#version 330

in vec3 normal;
in vec4 eye;
in vec4 color;
in vec2 tex;
in vec3 surfacePos;

uniform sampler2D texture;
uniform int useTexture;
uniform mat4 viewMatrix;

out vec4 frag_color;

void main () 
{
  vec4 light = vec4(-10.0, -2.0, -10.0, 0.0);
  vec3 lightIntensity = vec3(1.0, 1.0, 1.0); // White light
  vec3 lightPos = vec3(viewMatrix * light);  // World coordinate

  vec3 incidentRay = normalize(lightPos - surfacePos);
  vec3 n = normalize(normal);

  float brightness = max(0, dot(n, incidentRay));

  if (useTexture == 0) {
  	frag_color = vec4(brightness * lightIntensity * color.rgb, color.a);
  } else {
    vec4 c = texture2D(texture, tex);
    frag_color = vec4(brightness * lightIntensity * c.rgb, 1.0);
  }
}
