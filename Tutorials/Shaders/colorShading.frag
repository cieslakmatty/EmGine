#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D mySampler;

void main(){

	/*color = vec4(fragmentColor.r * (cos(fragmentPosition.x + time) + 1.0) * 0.5,
				fragmentColor.g * (cos(fragmentPosition.y + time) + 1.0) * 0.5,
				fragmentColor.b * (cos(fragmentPosition.x * fragmentPosition.y * time) + 1.0) * 0.5,
				fragmentColor.a);*/

	vec4 textureColor = texture(mySampler, fragmentUV);
	
	//color = textureColor * fragmentColor;

	/*color = vec4(fragmentColor.r * (sin(fragmentPosition.x * fragmentPosition.y * time) + 1.0) * 0.5,
				fragmentColor.g * (cos(fragmentPosition.x * fragmentPosition.y * time) + 1.0) * 0.5,
				fragmentColor.b * (cos(fragmentPosition.x * fragmentPosition.y * time) + 1.0) * 0.5,
				fragmentColor.a) * textureColor;*/
	color = fragmentColor * textureColor;
}