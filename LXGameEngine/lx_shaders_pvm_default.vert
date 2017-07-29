const char* lx_shaders_pvm_default_vert = "attribute vec3 a_position;\n\
attribute vec4 a_color;\n\
attribute vec2 a_texcoord;\n\
varying vec2 v_texcoord;\n\
varying vec4 v_color;\n\
uniform mat4 LX_PMATRIX;\n\
uniform mat4 LX_VMATRIX;\n\
uniform mat4 LX_MMATRIX;\n\
void main() {\n\
	v_texcoord = vec2(a_texcoord.x, 1.0 - a_texcoord.y);\n\
	v_color = a_color;\n\
	gl_Position = vec4(vec3(LX_PMATRIX * LX_VMATRIX * LX_MMATRIX * vec4(a_position, 1.0)), 1.0);\n\
}\n\
";