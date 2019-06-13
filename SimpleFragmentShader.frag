#version 330 core

// It was expressed that some drivers required this next line to function properly
precision highp float;

in  vec3 fragColor;
in  vec3 fragNormal;
in  vec3 fragPos;
in  vec4 FragPosLightSpace;

out vec4 gl_FragColor;

uniform vec3 lightPos;
uniform sampler2D shadowMap;

float ShadowCalculation(vec4 fragPosLightSpace, float bias)
{
// perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow    
    float shadow = (currentDepth - bias) > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

void main(void) {
    
    //ambient 
    float ambient = 0.3;
   
    //diffuse
    vec3 toLight = normalize(lightPos - fragPos);
    float diffuse = max(dot(fragNormal, toLight), 0.0);

    //float bias = max(0.05 * (1.0 - dot(fragNormal, toLight)), 0.005); 
    float shadow = ShadowCalculation(FragPosLightSpace, 0.001);      
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse)) * fragColor;    
    
    gl_FragColor = vec4(lighting, 1.0); 

}


