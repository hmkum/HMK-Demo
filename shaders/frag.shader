#version 330

uniform sampler2D tex;
uniform mat4 modelToWorldMatrix; // Model Matrix

in vec4 fragVertexPosition;
in vec2 fragTexCoords;
in vec3 fragVertexNormal;
in vec4 fragEyeSpacePos;
out vec4 outColor;

struct LightInfo
{
	vec4 position;
	vec3 intensity;
};
uniform LightInfo light;

struct FogParameters
{
   vec4 color; // Fog color
   float start; // This is only for linear fog
   float end; // This is only for linear fog
   float density; // For exp and exp2 equation

   int equation; // 0 = linear, 1 = exp, 2 = exp2
};
uniform FogParameters fogParams;
uniform bool isFogEnable;
uniform vec3 ambientLight;

float getFogFactor(FogParameters params, float fogCoord)
{
   float result = 0.0;
   if(params.equation == 0)
      result = (params.end-fogCoord) / (params.end-params.start);
   else if(params.equation == 1)
      result = exp(-params.density*fogCoord);
   else if(params.equation == 2)
      result = exp(-pow(params.density*fogCoord, 2.0));

   result = 1.0-clamp(result, 0.0, 1.0);

   return result;
}

void main()
{
    mat3 normalMatrix = transpose(inverse(mat3(modelToWorldMatrix)));
    vec3 eyeNorm = normalize(normalMatrix * fragVertexNormal);

    highp float sunDirection = max(dot(eyeNorm.xyz, -vec3(light.position)), 0.0);
    vec4 lightColor = vec4(ambientLight + (light.intensity * sunDirection), 0.0f);

    outColor = lightColor * texture(tex, fragTexCoords);

    if(isFogEnable)
    {
        // Add fog
    	float fogCoord = abs(fragEyeSpacePos.z/fragEyeSpacePos.w);
    	outColor = mix(outColor, fogParams.color, getFogFactor(fogParams, fogCoord));
    }
}
