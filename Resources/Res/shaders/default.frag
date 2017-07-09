varying vec2 v_texcoord;
varying vec4 v_color;
uniform sampler2D LX_TEXTURE0;
void main() {
	vec4 tex = texture2D(LX_TEXTURE0, v_texcoord);
	gl_FragColor = v_color * tex;
}
