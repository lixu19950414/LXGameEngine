#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include <vector>
#include "Node.h"
#include "PolygonInfo.h"
#include "SpriteFrame.h"
#include "ShaderCache.h"


class ParticleEmitter :
	public Node
{
public:
	struct Particle {
		GLfloat _lifeTime;
		glm::vec2 _worldPosition;
	};
public:
	ParticleEmitter();
	bool initWithParticleInfo(unsigned int maxParticles, unsigned int generateRate, const glm::vec2& velocity, float lifeTime, SpriteFrame* sp);
	~ParticleEmitter();

protected:
	void updateParticles();
	void visit(glm::mat4& parentTransform) override;
	void setupVAOAndVBO();
	void setShader(Shader* shader);
	void setSpriteFrame(SpriteFrame* spriteFrame);
	void fillPolygonInfo();
	virtual void draw() override;

private:
	unsigned int _maxParticels;
	unsigned int _generateRate;
	GLfloat _lifeTime;
	glm::vec2 _velocity;
	GLubyte _color[3];
	std::vector<Particle> _particles;
	PolygonInfo _polyInfo;

	SpriteFrame* _spriteFrame;
	Shader* _shader;
};

#endif
