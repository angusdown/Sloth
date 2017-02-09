#version 450 core

// ���ƹ���
#define MAX_LIGHT 4
// One terrain texture to tile n times in a edge
#define TERRAIN_TILE_NUMBLE 40.0f

uniform vec3 lightPosition[MAX_LIGHT];
uniform vec3 lightColor[MAX_LIGHT];
uniform float shininess = 32.0f;
uniform float reflectivity = 1.0f;
uniform vec3 skyColor;

uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;

out vec4 frag_out;

in DATA {
	vec3 pos;
	vec2 texCoord;
	vec3 normal;
} fs_in;

in vec3 worldPosition;
in vec3 toCameraVector;
in float visibility;

void main()
{
	vec4 blendMapColor = texture(blendMap, fs_in.texCoord);
	float backTextureAmount = 1.0f - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
	vec2 tiledCoords = fs_in.texCoord * TERRAIN_TILE_NUMBLE;
	vec4 backgroundTextureColor = texture(backgroundTexture, tiledCoords) * backTextureAmount;
	vec4 rTextureColor = texture(rTexture, tiledCoords) * blendMapColor.r;
	vec4 gTextureColor = texture(gTexture, tiledCoords) * blendMapColor.g;
	vec4 bTextureColor = texture(bTexture, tiledCoords) * blendMapColor.b;
	vec4 totalColor = backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor;

	vec3 n_ToCameraVector = normalize(toCameraVector);
	vec3 n_Normal = normalize(fs_in.normal);
	vec3 totalDiffuse = vec3(0.0f);
	vec3 totalSpecular = vec3(0.0f);
	vec3 n_ToLightVector;

	for(int i=0; i < MAX_LIGHT; ++i){
		// Diffuse
		n_ToLightVector = normalize(lightPosition[i] - worldPosition);
		float diff = max(dot(n_Normal, n_ToLightVector), 0.0f);
		totalDiffuse += lightColor[i] * diff;

		// Specular
		vec3 reflectDir = reflect(-n_ToLightVector, n_Normal);
		vec3 n_HalfWay = normalize(n_ToLightVector + n_ToCameraVector);
		float spec = pow(max(dot(n_Normal, n_HalfWay), 0.0f), shininess);
		totalSpecular += spec * lightColor[i] * reflectivity * 0.3;
	}
	//frag_out = vec4(totalDiffuse, 1.0f) * texture(tex0, fs_in.texCoord)  + vec4(totalSpecular, 1.0f);
	frag_out = vec4(totalDiffuse, 1.0f) * totalColor + vec4(totalSpecular, 1.0f);
	frag_out = mix(vec4(skyColor, 1.0f), frag_out, visibility);
	//frag_out = texture(backgroundTexture, fs_in.texCoord);
}