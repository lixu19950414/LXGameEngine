attribute vec3 a_position;
attribute vec4 a_color;
attribute vec2 a_texcoord;
varying vec2 v_texcoord;
varying vec4 v_color;
uniform mat4 LX_PMATRIX;
uniform mat4 LX_VMATRIX;
uniform mat4 LX_MMATRIX;
void main() {
	v_texcoord = a_texcoord;
	v_color = a_color;
	gl_Position = LX_PMATRIX * LX_VMATRIX * LX_MMATRIX * vec4(a_position, 1.0);
}
