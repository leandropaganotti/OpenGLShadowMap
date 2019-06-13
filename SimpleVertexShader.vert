#version 330 core

in  vec3 inPosition;
in  vec3 inColor;
in  vec3 inNormal;


uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 biasMatrix;
uniform mat4 depthProjection;
uniform mat4 depthView;

out vec3 fragColor;
out vec3 fragNormal;
out vec3 fragPos;
out vec4 FragPosLightSpace;

void main(void) {

    gl_Position = P * V * M * vec4(inPosition, 1.0);

    fragColor = inColor;
    fragPos = vec3(M * vec4(inPosition, 1.0));
    fragNormal = vec3(transpose(inverse(M)) * vec4(inNormal, 0.0));

    FragPosLightSpace = depthProjection * depthView * M * vec4(inPosition, 1.0);

}
