#version 330 core

in vec4 fragmentColor;
in vec2 fragmentUV;

uniform sampler2D texture0;

void main() {

	vec4 sampled = texture(texture0, fragmentUV);
	gl_FragColor = fragmentColor * sampled;

}