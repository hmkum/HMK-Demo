#version 330

uniform samplerCube tex;

in vec3 fragTexCoords;
out vec4 outColor;

void main()
{
    outColor = texture(tex, fragTexCoords);
}
