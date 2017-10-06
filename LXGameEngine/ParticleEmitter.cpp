#include "stdafx.h"
#include "ParticleEmitter.h"
#include "Director.h"


ParticleEmitter::ParticleEmitter():
_maxParticels(0),
_lifeTime(0.0),
_velocity(0.0, 0.0),
_generateRate(0),
_spriteFrame(nullptr),
_shader(nullptr)
{
	_color[0] = 255; _color[1] = 255; _color[2] = 255;
	setShader(ShaderCache::getInstance()->getGlobalShader(ShaderCache::LX_SHADERS_PARTICLE));
}

bool ParticleEmitter::initWithParticleInfo(unsigned int maxParticles, unsigned int generateRate, const glm::vec2& velocity, float lifeTime, SpriteFrame* sp)
{
	_maxParticels = maxParticles;
	_lifeTime = lifeTime;
	_velocity = velocity;
	_generateRate = generateRate;
	setSpriteFrame(sp);
	return true;
}


ParticleEmitter::~ParticleEmitter()
{
	LX_SAFE_RELEASE_NULL(_shader);
	LX_SAFE_RELEASE_NULL(_spriteFrame);
	_particles.clear();
}

void ParticleEmitter::updateParticles()
{
	// Update existing particles
	float dt = Director::getInstance()->getDeltaTime();
	auto it = _particles.begin();
	while (it != _particles.end()) {
		it->_lifeTime -= dt;
		if (it->_lifeTime <= 0.0) {
			it = _particles.erase(it);
		}
		else {
			it->_worldPosition += _velocity * dt;
			++it;
		}
	}
	// Create new particles
	int leftSize = _maxParticels - _particles.size();
	int newParticlesCnt = _generateRate * dt;
	if (leftSize >= newParticlesCnt) {
		glm::vec4 worldPos = _modelTransform * glm::vec4(0.0, 0.0, 0.0, 1.0);
		for (int i = 0; i < newParticlesCnt; ++i) {
			Particle p;
			p._worldPosition = worldPos;
			p._lifeTime = _lifeTime;
			_particles.push_back(p);
		}
	}
	else if (leftSize > 0) {
		glm::vec4 worldPos = _modelTransform * glm::vec4(0.0, 0.0, 0.0, 1.0);
		for (int i = 0; i < leftSize; ++i) {
			Particle p;
			p._worldPosition = worldPos;
			p._lifeTime = _lifeTime;
			_particles.push_back(p);
		}
	}
	else {
		//Do nothing
	}
}

void ParticleEmitter::visit(glm::mat4 & parentTransform)
{
	sortChildren();
	updateTransform();
	_modelTransform = parentTransform * _transform;
	// For particles, should update particles.
	updateParticles();
	updateAABB();
	auto start = _children.begin();
	// visit nodes with z < 0
	for (; start != _children.end(); ++start) {
		if ((*start)->getLocalZ() < 0) {
			(*start)->visit(_modelTransform);
		}
		else {
			break;
		}
	}
	draw();
	// visit nodes with z >= 0
	for (; start != _children.end(); ++start) {
		(*start)->visit(_modelTransform);
	}
}

void ParticleEmitter::setupVAOAndVBO()
{
	//Particle should recreate vao and vbo every frame
	fillPolygonInfo();

	//Upload vertex data
	if (_vao == 0) {
		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);
		glGenBuffers(1, &_ebo);

		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, _polyInfo.getVertsCount() * sizeof(V3F_C4B_T2F), _polyInfo.getVerts(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _polyInfo.getIndicesCount() * sizeof(GLuint), _polyInfo.getIndices(), GL_DYNAMIC_DRAW);

		//int a_position = _shader->getAttributeLocation("a_position");
		//int a_color = _shader->getAttributeLocation("a_color");
		//int a_texcoord = _shader->getAttributeLocation("a_texcoord");

		glVertexAttribPointer(_shader->getAttributeLocation("a_position"), 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*)offsetof(V3F_C4B_T2F, _vertices));
		glEnableVertexAttribArray(_shader->getAttributeLocation("a_position"));
		glVertexAttribPointer(_shader->getAttributeLocation("a_color"), 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B_T2F), (GLvoid*)offsetof(V3F_C4B_T2F, _color));
		glEnableVertexAttribArray(_shader->getAttributeLocation("a_color"));
		glVertexAttribPointer(_shader->getAttributeLocation("a_texcoord"), 2, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*)offsetof(V3F_C4B_T2F, _uv));
		glEnableVertexAttribArray(_shader->getAttributeLocation("a_texcoord"));

		glBindVertexArray(0);
	}
	else {
		glBindVertexArray(_vao);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, _polyInfo.getVertsCount() * sizeof(V3F_C4B_T2F), _polyInfo.getVerts(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _polyInfo.getIndicesCount() * sizeof(GLuint), _polyInfo.getIndices(), GL_DYNAMIC_DRAW);

		glBindVertexArray(0);
	}
}

void ParticleEmitter::setShader(Shader * shader)
{
	if (_shader != nullptr) {
		_shader->release();
	}
	shader->retain();
	_shader = shader;
}

void ParticleEmitter::setSpriteFrame(SpriteFrame * spriteFrame)
{
	if (_spriteFrame != nullptr) {
		_spriteFrame->release();
	}
	spriteFrame->retain();
	_spriteFrame = spriteFrame;
}

void ParticleEmitter::fillPolygonInfo()
{
	_polyInfo.clear();
	const glm::vec2& size = _spriteFrame->getPixelRect().getSize();
	int count = 0;
	for (auto it : _particles) {
		V3F_C4B_T2F tmpLB, tmpRB, tmpRT, tmpLT;
		glm::vec2 lbPos = it._worldPosition + glm::vec2(-size.x / 2, -size.y / 2);
		glm::vec2 rbPos = it._worldPosition + glm::vec2(size.x / 2, -size.y / 2);
		glm::vec2 rtPos = it._worldPosition + glm::vec2(size.x / 2, size.y / 2);
		glm::vec2 ltPos = it._worldPosition + glm::vec2(-size.x / 2, size.y / 2);

		tmpLB.setVertices(lbPos.x, lbPos.y, 0.0);
		tmpRB.setVertices(rbPos.x, rbPos.y, 0.0);
		tmpRT.setVertices(rtPos.x, rtPos.y, 0.0);
		tmpLT.setVertices(ltPos.x, ltPos.y, 0.0);

		GLubyte thisOpacity = (int)((float)(it._lifeTime) / _lifeTime * _opacity);

		tmpLB.setColor(_color[0], _color[1], _color[2], thisOpacity);
		tmpRB.setColor(_color[0], _color[1], _color[2], thisOpacity);
		tmpRT.setColor(_color[0], _color[1], _color[2], thisOpacity);
		tmpLT.setColor(_color[0], _color[1], _color[2], thisOpacity);

		tmpLB.setUV(_spriteFrame->getLBTexCoord().x, _spriteFrame->getLBTexCoord().y);
		tmpRB.setUV(_spriteFrame->getRBTexCoord().x, _spriteFrame->getRBTexCoord().y);
		tmpRT.setUV(_spriteFrame->getRTTexCoord().x, _spriteFrame->getRTTexCoord().y);
		tmpLT.setUV(_spriteFrame->getLTTexCoord().x, _spriteFrame->getLTTexCoord().y);

		_polyInfo.pushVert(tmpLB);
		_polyInfo.pushVert(tmpRB);
		_polyInfo.pushVert(tmpRT);
		_polyInfo.pushVert(tmpLT);

		// 013123
		_polyInfo.pushIndices(count * 4);
		_polyInfo.pushIndices(count * 4 + 1);
		_polyInfo.pushIndices(count * 4 + 3);

		_polyInfo.pushIndices(count * 4 + 1);
		_polyInfo.pushIndices(count * 4 + 2);
		_polyInfo.pushIndices(count * 4 + 3);
		++count;
	}
	
}

void ParticleEmitter::draw()
{
	setupVAOAndVBO();
	_shader->use();
	_shader->updateBuiltinUniforms(glm::mat4());

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
	_spriteFrame->bindTexture();
	glBlendFunc(_blendSrc, _blendDst);
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _polyInfo.getIndicesCount(), GL_UNSIGNED_INT, 0);
	//LX_LOG("%d\n", _polyInfo.getIndicesCount());
	glBindVertexArray(0);
}
