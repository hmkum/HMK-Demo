#version 330

layout(location = 0) in vec3 vertexPosition;

uniform mat4 worldToCameraMatrix; // View(World) Matrix
uniform mat4 cameraToClipMatrix; // Projection Matrix

out vec3 fragTexCoords;

void main()
{
    fragTexCoords = vec3(vertexPosition);
	vec4 MVP = cameraToClipMatrix * worldToCameraMatrix * vec4(vertexPosition, 1.0);
	gl_Position =  MVP;
}
