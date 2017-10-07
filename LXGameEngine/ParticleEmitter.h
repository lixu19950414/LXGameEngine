#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include <vector>
#include <string>
#include "Node.h"
#include "PolygonInfo.h"
#include "SpriteFrame.h"
#include "ShaderCache.h"


class ParticleEmitter :
	public Node
{
public:
	struct Particle {
		
		float _leftLifespan;
		float _particleLifespan;
		
		float _startPositionX;
		float _finishPositionX;
		float _startPositionY;
		float _finishPositionY;

		float _startParticleSize;
		float _finishParticleSize;
		float _startColorRed;
		float _startColorGreen;
		float _startColorBlue;
		float _startColorAlpha;
		float _finishColorRed;
		float _finishColorGreen;
		float _finishColorBlue;
		float _finishColorAlpha;
	};
public:
	ParticleEmitter();
	bool initWithPlist(const std::string& plistName);
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
	std::vector<Particle> _particles;
	PolygonInfo _polyInfo;

	SpriteFrame* _spriteFrame;
	Shader* _shader;

	int _maxParticles;
	int _generateRate;
	float _particleLifespan;
	float _particleLifespanVariance;

	float _sourcePositionVariancex;
	float _sourcePositionVariancey;

	float _startParticleSize;
	float _startParticleSizeVariance;
	float _finishParticleSize;
	float _finishParticleSizeVariance;

	float _angle;
	float _angleVariance;
	float _speed;
	float _speedVariance;

	float _startColorRed;
	float _startColorGreen;
	float _startColorBlue;
	float _startColorAlpha;
	float _startColorVarianceRed;
	float _startColorVarianceGreen;
	float _startColorVarianceBlue;
	float _startColorVarianceAlpha;
	float _finishColorRed;
	float _finishColorGreen;
	float _finishColorBlue;
	float _finishColorAlpha;
	float _finishColorVarianceRed;
	float _finishColorVarianceGreen;
	float _finishColorVarianceBlue;
	float _finishColorVarianceAlpha;

	int _blendFuncDestination;
	int _blendFuncSource;
};

#endif
