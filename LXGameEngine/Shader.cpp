#include "stdafx.h"
#include "Shader.h"
#include "Camera.h"

const char * Shader::ATTRIB_NAME_POSITION = "a_position";
const char * Shader::ATTRIB_NAME_COLOR = "a_color";
const char * Shader::ATTRIB_NAME_NORMAL = "a_normal";
const char * Shader::ATTRIB_NAME_TEXCOORD = "a_texcoord";


const char* Shader::UNIFORM_NAME_LX_PMATRIX = "LX_PMATRIX";
const char* Shader::UNIFORM_NAME_LX_VMATRIX = "LX_VMATRIX";
const char* Shader::UNIFORM_NAME_LX_MMATRIX = "LX_MMATRIX";

const char* Shader::UNIFORM_NAME_LX_TEXTURE0 = "LX_TEXTURE0";
const char* Shader::UNIFORM_NAME_LX_TEXTURE1 = "LX_TEXTURE1";
const char* Shader::UNIFORM_NAME_LX_TEXTURE2 = "LX_TEXTURE2";
const char* Shader::UNIFORM_NAME_LX_TEXTURE3 = "LX_TEXTURE3";

Shader::Shader():
_vertexID(0),
_fragmentID(0),
_programID(0)
{
};

Shader::~Shader()
{
	clear();
}

bool Shader::initWithFiles(const std::string & vertex, const std::string & frag)
{
	LX_FU::Data* vertexData = LX_FU::getDataFromFile(vertex);
	if (!vertexData->loadSucceed())
	{
		delete vertexData;
		return false;
	}
	LX_FU::Data* fragData = LX_FU::getDataFromFile(frag);
	if (!fragData->loadSucceed()) {
		delete vertexData;
		delete fragData;
		return false;
	}
	std::string vertexSource = vertexData->getString();
	std::string fragSource = fragData->getString();

	delete vertexData;
	delete fragData;
	return initWithByteArrays(vertexSource.c_str(), fragSource.c_str());
}

bool Shader::initWithByteArrays(const char * vertexShader, const char * fragmentShader)
{
	if (compileShader(GL_VERTEX_SHADER, vertexShader) == 0) {
		clear();
		return false;
	}
	if (compileShader(GL_FRAGMENT_SHADER, fragmentShader) == 0) {
		clear();
		return false;
	}
	if (link() == 0) {
		clear();
		return false;
	}

	parseVertexAttributes();
	parseUniforms();
	use();
	initializeUniforms();
	return true;
}

GLint Shader::getAttributeLocation(const std::string & attrib)
{
	auto it = _attributes.find(attrib);
	if (it != _attributes.end())
		return it->second;
	return -1;
}

GLint Shader::getUniformLocation(const std::string & uniform)
{
	auto it = _uniforms.find(uniform);
	if (it != _uniforms.end()) {
		return it->second;
	}
	return -1;
}

GLuint Shader::compileShader(GLenum type, const char * shaderSource)
{
	GLuint shader = 0;
	GLint compiled = 0;

	shader = glCreateShader(type);
	if (shader == 0)
	{
		return 0;
	}
	switch (type) {
	case GL_VERTEX_SHADER:
		_vertexID = shader;
		break;
	case GL_FRAGMENT_SHADER:
		_fragmentID = shader;
		break;
	default:
		glDeleteShader(shader);
		return 0;
	}
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLint infoLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
		if (infoLength > 1)
		{
			GLchar* infoLog = new GLchar[infoLength];
			glGetShaderInfoLog(shader, infoLength, NULL, infoLog);
			LX_LOG("COMPILE_SHADER_ERROR:\n%s", infoLog);
			delete []infoLog;
		}
		return 0;
	}
	return shader;
}

void Shader::bindVertexAttribLocation()
{
	glBindAttribLocation(_programID, ATTRIB_POS_POSITION, ATTRIB_NAME_POSITION);
	glBindAttribLocation(_programID, ATTRIB_POS_COLOR, ATTRIB_NAME_COLOR);
	glBindAttribLocation(_programID, ATTRIB_POS_TEXCOORD, ATTRIB_NAME_TEXCOORD);
	glBindAttribLocation(_programID, ATTRIB_POS_NORMAL, ATTRIB_NAME_NORMAL);
}

GLuint Shader::link()
{
	GLuint program;
	GLint linked = 0;
	program = glCreateProgram();
	if (program == 0) {
		return 0;
	}
	_programID = program;
	glAttachShader(program, _vertexID);
	glAttachShader(program, _fragmentID);

	bindVertexAttribLocation();

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if(!linked){
		GLint infoLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);
		if(infoLength > 1){
			GLchar* infoLog = new GLchar[infoLength];
			glGetProgramInfoLog(program, infoLength, NULL, infoLog);
			LX_LOG("LINK_PROGRAM_ERROR:\n%s", infoLog);
			delete[]infoLog;
		}
		return 0;
	}
	return program;
}
void Shader::parseVertexAttributes()
{
	GLint maxVertexAttribLen = 0;
	GLint maxVertexAttribNum = 0;
	glGetProgramiv(_programID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxVertexAttribLen);
	glGetProgramiv(_programID, GL_ACTIVE_ATTRIBUTES, &maxVertexAttribNum);

	for (GLint i = 0; i < maxVertexAttribNum; i++)
	{
		GLenum type;
		GLint size;
		GLint location;
		GLchar* attribName = new GLchar[maxVertexAttribLen];
		glGetActiveAttrib(_programID, i, maxVertexAttribLen, NULL, &size, &type, attribName);
		location = glGetAttribLocation(_programID, attribName);
		_attributes.emplace(attribName, location);
	}
}

void Shader::parseUniforms()
{
	GLint maxUniformLen = 0;
	GLint maxUniformNum = 0;
	glGetProgramiv(_programID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformLen);
	glGetProgramiv(_programID, GL_ACTIVE_UNIFORMS, &maxUniformNum);

	for (GLint i = 0; i < maxUniformNum; i++)
	{
		GLenum type;
		GLint size;
		GLint location;
		GLchar* uniformName = new GLchar[maxUniformLen];
		glGetActiveUniform(_programID, i, maxUniformLen, NULL, &size, &type, uniformName);
		location = glGetUniformLocation(_programID, uniformName);
		_uniforms.emplace(uniformName, location);
	}
}
void Shader::initializeUniforms()
{
	if (hasUniform(UNIFORM_NAME_LX_TEXTURE0))
		glUniform1i(getUniformLocation(UNIFORM_NAME_LX_TEXTURE0), 0);
	if (hasUniform(UNIFORM_NAME_LX_TEXTURE1))
		glUniform1i(getUniformLocation(UNIFORM_NAME_LX_TEXTURE1), 1);
	if (hasUniform(UNIFORM_NAME_LX_TEXTURE2))
		glUniform1i(getUniformLocation(UNIFORM_NAME_LX_TEXTURE2), 2);
	if (hasUniform(UNIFORM_NAME_LX_TEXTURE3))
		glUniform1i(getUniformLocation(UNIFORM_NAME_LX_TEXTURE3), 3);
}
;

void Shader::use()
{
	glUseProgram(_programID);
}

void Shader::updateBuiltinUniforms(glm::mat4 model)
{
	auto instance = Camera::getInstance();
	glUniformMatrix4fv(getUniformLocation(UNIFORM_NAME_LX_PMATRIX), 1, GL_FALSE, glm::value_ptr(instance->getProjectionMatrix()));
	glUniformMatrix4fv(getUniformLocation(UNIFORM_NAME_LX_VMATRIX), 1, GL_FALSE, glm::value_ptr(instance->getViewMatrix()));
	glUniformMatrix4fv(getUniformLocation(UNIFORM_NAME_LX_MMATRIX), 1, GL_FALSE, glm::value_ptr(model));
}

void Shader::clear()
{
	if (_programID) {
		glDeleteProgram(_programID);
		_programID = 0;
	}
	if (_vertexID) {
		glDeleteShader(_vertexID);
		_vertexID = 0;
	}
	if (_fragmentID) {
		glDeleteShader(_fragmentID);
		_fragmentID = 0;
	}
	_attributes.clear();
	_uniforms.clear();
}

void Shader::dump()
{
	LX_LOG("DumpShader:\n");
	LX_LOG("Attributes:\n");
	for (auto it : _attributes) {
		LX_LOG("%s:%d\n", it.first.c_str(), it.second);
	}
	LX_LOG("Uniforms:\n");
	for (auto it : _uniforms) {
		LX_LOG("%s:%d\n", it.first.c_str(), it.second);
	}
}
