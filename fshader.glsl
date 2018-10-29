#version 330

in vec3 normal;
in vec4 eye;
in vec4 color;
in vec2 tex;
in vec3 surfacePos;

uniform sampler2D texture;
uniform int useTexture;
uniform mat4 viewMatrix;
uniform int light0ON;
uniform int light1ON;

out vec4 finalColor;


struct lightSource
{
  vec4 position;
  vec3 intensity;
  float attenuation;
  bool on;
};
const int numberOfLights = 2;
lightSource lights[numberOfLights];

lightSource light0 = lightSource(
	vec4(-18, 2, 13, 0.0),
	vec3(1.0, 1.0, 1.0),
	0.005,
	true
);

lightSource light1 = lightSource(
    vec4(0.0, -2.0,  0.0, 1.0),
    vec3(1.0, 1.0, 1.0),
    0.005,
    true
);

void main () 
{	

	light0.on = light0ON > 0;
	light1.on = light1ON > 0;

	lights[0] = light0;
	lights[1] = light1;

	// Defining Parameters 
	float ambientCoefficient = 0.1;
	float materialShininess = 10.0;


	// Defining actual color
	vec4 surfaceColor;
	if (useTexture == 0) {
		surfaceColor = color;
	} else {
		surfaceColor = texture2D(texture, tex);
	}


    // Ambient
	vec3 ambient = ambientCoefficient * surfaceColor.rgb;

	vec3 totalLighting = ambient;

	for (int index = 0; index < numberOfLights; index++) {

		if (!lights[index].on) {
			continue;
		}

		// Defining Light Source
		vec4 light = lights[index].position;
		vec3 lightIntensity = lights[index].intensity; // White light
		vec3 lightPos = vec3(viewMatrix * light);  // World coordinate
		float lightAttenuation = lights[index].attenuation;

		
		// Defining vectors
		vec3 surfaceToLight = normalize(lightPos - surfacePos);
		vec3 surfaceToCamera = normalize(vec3(eye) - surfacePos);
		vec3 n = normalize(normal);


		// Diffuse
		float diffuseCoefficient = max(0.0, dot(n, surfaceToLight));
		vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * lightIntensity;


		// Specular
		float specularCoefficient = 0.0;
		if(diffuseCoefficient > 0.0)
			specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), materialShininess);
		vec3 specular = specularCoefficient * surfaceColor.rgb * lightIntensity;


		// Attenuation
	    float distanceToLight = length(lightPos - surfacePos);
	    float attenuation = 1.0 / (1.0 + lightAttenuation * pow(distanceToLight, 2));

	    // Linear color (color before gamma correction)
	    vec3 linearColor = attenuation*(diffuse + specular);

	    totalLighting += linearColor;
	}
    
    // Final color (after gamma correction)
    vec3 gamma = vec3(1.0/2.2);
    finalColor = vec4(pow(totalLighting, gamma), surfaceColor.a);  
}
