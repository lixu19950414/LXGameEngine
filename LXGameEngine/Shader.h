#ifndef SHADER_H
#define SHADER_H

#include "Ref.h"

class Shader : public Ref
{
	static const char* ATTRIB_NAME_POSITION;
	static const char* ATTRIB_NAME_COLOR;
	static const char* ATTRIB_NAME_TEXCOORD;
	static const char* ATTRIB_NAME_NORMAL;

	static const char* UNIFORM_NAME_LX_PMATRIX;
	static const char* UNIFORM_NAME_LX_VMATRIX;
	static const char* UNIFORM_NAME_LX_MMATRIX;

	static const char* UNIFORM_NAME_LX_TEXTURE0;
	static const char* UNIFORM_NAME_LX_TEXTURE1;
	static const char* UNIFORM_NAME_LX_TEXTURE2;
	static const char* UNIFORM_NAME_LX_TEXTURE3;
public:

	enum ATTRIB_POS {
		ATTRIB_POS_POSITION = 0,
		ATTRIB_POS_COLOR,
		ATTRIB_POS_TEXCOORD,
		ATTRIB_POS_NORMAL,
	};

public:
	Shader();
	~Shader();
	bool initWithFiles(const std::string& vertex, const std::string& frag);
	bool initWithByteArrays(const char* vertexShader, const char* fragmentShader);
	
	GLint getAttributeLocation(const std::string& attrib);
	GLint getUniformLocation(const std::string& uniform);
	
	void use();
	void updateBuiltinUniforms(glm::mat4 model);

	void clear();
	void dump();

	inline bool hasUniform(const std::string& name) { return getUniformLocation(name) != -1; };
private:
	GLuint compileShader(GLenum type, const char* shaderSource);
	void bindVertexAttribLocation();
	GLuint link();

	void parseVertexAttributes();
	void parseUniforms();
	void initializeUniforms();

private:
	GLuint _vertexID;
	GLuint _fragmentID;
	GLuint _programID;

	std::unordered_map<std::string, GLint> _attributes;
	std::unordered_map<std::string, GLint> _uniforms;
};


#endif /* shader_hpp */
