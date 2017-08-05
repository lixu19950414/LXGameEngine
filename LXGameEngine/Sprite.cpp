#include "stdafx.h"
#include "Sprite.h"
#include "ShaderCache.h"
#include "Camera.h"

Sprite::Sprite() :
_texture(nullptr),
_shader(nullptr),
_vertsDirty(true)
{
	_color[0] = _color[1] = _color[2] = 255;
	_shader = ShaderCache::getInstance()->getGlobalShader(ShaderCache::LX_SHADERS_PVM_DEFAULT);
	_shader->retain();
}


Sprite::~Sprite()
{
	releaseCurrentTexture();
	_shader->release();
}

bool Sprite::initWithFile(const std::string & filename)
{
	Texture2D* texture = new (std::nothrow) Texture2D();
	if (!texture->initWithFileName(filename)) {
		delete texture;
		return false;
	}
	texture->autoRelease();
	return initWithTexture(texture);
}

bool Sprite::initWithTexture(Texture2D * texture)
{
	releaseCurrentTexture();
	_texture = texture;
	_texture->retain();

	GLint pixelWidth = texture->getPixelWidth();
	GLint pixelHeight = texture->getPixelHeight();

	setContentSize(pixelWidth, pixelHeight);
	
	return true;
}

void Sprite::draw()
{
	setupVAOAndVBO();
	_shader->use();
	_shader->updateBuiltinUniforms(_modelTransform);
	
	/*auto instance = Camera::getInstance();
	glm::mat4 temp = instance->getProjectionMatrix() * instance->getViewMatrix() * _modelTransform;
	std::vector<V3F_C4B_T2F>* vertices = static_cast<std::vector<V3F_C4B_T2F>*>(_polyInfo.getVerts());
	for (auto it : *vertices) {
		auto xx = it._vertices[0];
		auto tt = it._vertices[1];
		auto zz = it._vertices[2];
		glm::vec4 pos = glm::vec4(xx, tt, zz, 1.0);
		glm::vec4 finalPos = temp * pos;
	}*/

	glActiveTexture(GL_TEXTURE0); //在绑定纹理之前先激活纹理单元
	_texture->bind();
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _polyInfo.getIndicesCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Sprite::dump()
{
	LX_LOG("Sprite::Dump\n");
	_texture->dump();
	LX_LOG("AABB: origin(%d, %d) size(%d, %d)\n", _aabb.getOrigin().x, _aabb.getOrigin().y, _aabb.getSize().x, _aabb.getSize().y);
}

void Sprite::setContentSize(GLfloat width, GLfloat height)
{
	if (_contentSize.x != width || _contentSize.y != height)
	{
		_contentSize = glm::vec2(width, height);
		_vertsDirty = true;
		_aabbDirty = true;
	}
}

void Sprite::setAnchorPoint(GLfloat x, GLfloat y)
{
	if (_anchorPoint.x != x || _contentSize.y != y)
	{
		_anchorPoint = glm::vec2(x, y);
		_vertsDirty = true;
		_aabbDirty = true;
	}
}

void Sprite::setOpacity(GLubyte opacity)
{
	if (_opacity != opacity)
	{
		_opacity = opacity;
		_vertsDirty = true;
	}
}

void Sprite::setColor(GLubyte r, GLubyte g, GLubyte b)
{
	if (_color[0] != r || _color[1] != g || _color[2] != b) {
		_color[0] = r;
		_color[1] = g;
		_color[2] = b;
		_vertsDirty = true;
	}
}

void Sprite::releaseCurrentTexture()
{
	if (_texture != nullptr) {
		_texture->release();
	}
}

void Sprite::fillPolygonInfo()
{
	GLfloat width = _contentSize.x;
	GLfloat height = _contentSize.y;

	GLfloat anchorX = _anchorPoint.x;
	GLfloat anchorY = _anchorPoint.y;

	GLfloat offSetX = -(width * anchorX);
	GLfloat offSetY = -(height * anchorY);

	_polyInfo.clear();
	_lb.setVertices(offSetX, offSetY, .0f);
	_lt.setVertices(offSetX, height + offSetY, .0f);
	_rb.setVertices(width + offSetX, offSetY, .0f);
	_rt.setVertices(width + offSetX, height +  offSetY, .0f);

	_lb.setColor(_color[0], _color[1], _color[2], _opacity);
	_lt.setColor(_color[0], _color[1], _color[2], _opacity);
	_rb.setColor(_color[0], _color[1], _color[2], _opacity);
	_rt.setColor(_color[0], _color[1], _color[2], _opacity);

	_lb.setUV(.0f, .0f);
	_lt.setUV(.0f, 1.0f);
	_rb.setUV(1.0f, 0.0f);
	_rt.setUV(1.0f, 1.0f);

	_polyInfo.pushVert(_lt);
	_polyInfo.pushVert(_lb);
	_polyInfo.pushVert(_rb);
	_polyInfo.pushVert(_rt);

	_polyInfo.pushIndices(0);
	_polyInfo.pushIndices(1);
	_polyInfo.pushIndices(2);
	_polyInfo.pushIndices(0);
	_polyInfo.pushIndices(2);
	_polyInfo.pushIndices(3);
}

void Sprite::setupVAOAndVBO()
{
	if (_vao == 0) {
		fillPolygonInfo();

		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);
		glGenBuffers(1, &_ebo);
		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, _polyInfo.getVertsCount() * sizeof(V3F_C4B_T2F), _polyInfo.getVerts(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _polyInfo.getIndicesCount() * sizeof(GLuint), _polyInfo.getIndices(), GL_DYNAMIC_DRAW);
		// 指定顶点属性
		glVertexAttribPointer(_shader->getAttributeLocation("a_position"), 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*)offsetof(V3F_C4B_T2F, _vertices));
		glEnableVertexAttribArray(_shader->getAttributeLocation("a_position"));
		glVertexAttribPointer(_shader->getAttributeLocation("a_color"), 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B_T2F), (GLvoid*)offsetof(V3F_C4B_T2F, _color));
		glEnableVertexAttribArray(_shader->getAttributeLocation("a_color"));
		glVertexAttribPointer(_shader->getAttributeLocation("a_texcoord"), 2, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*)offsetof(V3F_C4B_T2F, _uv));
		glEnableVertexAttribArray(_shader->getAttributeLocation("a_texcoord"));

		glBindVertexArray(0);
	}
	else if(_vertsDirty){
		fillPolygonInfo();

		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, _polyInfo.getVertsCount() * sizeof(V3F_C4B_T2F), _polyInfo.getVerts(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _polyInfo.getIndicesCount() * sizeof(GLuint), _polyInfo.getIndices(), GL_DYNAMIC_DRAW);
		glBindVertexArray(0);
	}
	_vertsDirty = false;
}


