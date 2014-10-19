#version 330

layout(location = 0) in vec3 vertexPosition;
layout(location = 2) in vec2 texCoords;
layout(location = 3) in vec3 vertexNormal;

uniform mat4 modelToWorldMatrix; // Model Matrix
uniform mat4 worldToCameraMatrix; // View(World) Matrix
uniform mat4 cameraToClipMatrix; // Projection Matrix

out vec2 fragTexCoords;
out vec3 fragVertexNormal;
out vec4 fragEyeSpacePos;
out mat3 normalMatrix;

void main()
{
    fragVertexNormal = vertexNormal;
    fragTexCoords = texCoords;
    fragEyeSpacePos = worldToCameraMatrix * modelToWorldMatrix * vec4(vertexPosition, 1.0);

    normalMatrix = transpose(inverse(mat3(modelToWorldMatrix)));

    gl_Position =  cameraToClipMatrix * worldToCameraMatrix * modelToWorldMatrix * vec4(vertexPosition, 1.0);
}
