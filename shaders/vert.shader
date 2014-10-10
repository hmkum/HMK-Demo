#version 330

layout(location = 0) in vec4 vertexPosition;
layout(location = 2) in vec2 texCoords;
layout(location = 3) in vec3 vertexNormal;

uniform mat4 modelToWorldMatrix; // Model Matrix
uniform mat4 worldToCameraMatrix; // View(World) Matrix
uniform mat4 cameraToClipMatrix; // Projection Matrix

out vec2 fragTexCoords;
out vec4 fragVertexPosition;
out vec3 fragVertexNormal;
out vec4 fragEyeSpacePos;

void main()
{
	fragVertexPosition = vertexPosition;
	fragVertexNormal = vertexNormal;
    fragTexCoords = texCoords;
    gl_Position =  cameraToClipMatrix * worldToCameraMatrix * modelToWorldMatrix * vertexPosition;

    fragEyeSpacePos = worldToCameraMatrix * modelToWorldMatrix * vertexPosition;
}
