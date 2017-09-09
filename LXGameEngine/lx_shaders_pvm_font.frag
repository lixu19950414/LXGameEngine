const char* lx_shaders_pvm_font_frag = "varying vec2 v_texcoord;\n\
varying vec4 v_color;\n\
uniform sampler2D LX_TEXTURE0;\n\
void main() {\n\
	vec4 tex = texture2D(LX_TEXTURE0, v_texcoord);\n\
	gl_FragColor = v_color * tex.r;\n\
	//gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n\
}\n\
";