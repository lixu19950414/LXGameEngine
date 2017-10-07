#include "stdafx.h"
#include "Director.h"
#include "AutoReleasePool.h"
#include "Scene.h"
#include "Game.h"
#include "Common.h"
#include "Scheduler.h"
#include "FontCache.h"
#include "ShaderCache.h"
#include "TextureGridCache.h"

Director* g_pDirector = nullptr;

Director* Director::getInstance()
{
	if (!g_pDirector)
	{
		g_pDirector = new Director();
	}
	return g_pDirector;
}

Director::Director() :
	_FPS(60),
	_SPF(1.0f/60),
	_deltaTime(0.0f),
	_displayLinkStatus(true),
	_drawCallsCount(0),
	_vertsCount(0),
	_vao(0),
	_vbo(0),
	_ebo(0),
	_shader(nullptr)
{
	_lastUpdateTime = std::chrono::steady_clock::now();
	_shader = ShaderCache::getInstance()->getGlobalShader(ShaderCache::GLOBAL_SHADERS::LX_SHADERS_PVM_FONT);
	_shader->retain();
}


Director::~Director()
{
	if (_vao) {
		glDeleteVertexArrays(1, &_vao);
		_vao = 0;
	}
	if (_vbo) {
		glDeleteBuffers(1, &_vbo);
		_vbo = 0;
	}
	if (_ebo) {
		glDeleteBuffers(1, &_ebo);
		_ebo = 0;
	}
	LX_SAFE_RELEASE_NULL(_shader);
}

bool Director::mainLoop()
{
	// Update timer
	calculateDeltaTime();
	Scheduler::getInstance()->update(_deltaTime);

	// Clear drawcall info
	clearDisplayCounts();
	// Draw scene
	onBeginResetGLState();
	Scene::getInstance()->visit();
	AutoReleasePool::getInstance()->executeClear();
	// Show drawcall info
	if (_displayLinkStatus) {
		drawDisplayStatus();
	}
	
	// Game loop
	return Game::getInstance()->loop();
}

bool Director::start()
{
	Game::getInstance()->start();
	
	return true;
}

void Director::onBeginResetGLState()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

float Director::calculateDeltaTime()
{
	auto thisUpdateTime = std::chrono::steady_clock::now();
	float tempTime = std::chrono::duration_cast<std::chrono::duration<float>>(thisUpdateTime - _lastUpdateTime).count();
	_lastUpdateTime = thisUpdateTime;
	_deltaTime = std::max(0.0f, tempTime);
	return _deltaTime;
}

void Director::drawDisplayStatus()
{
	_polyInfo.clear();

	std::string drawCallWords = "GL CALLS: ";
	char str1[10];
	sprintf(str1, "%d", _drawCallsCount);
	drawCallWords += str1;
	std::string vertsWords = "GL VERTS: ";
	char str2[10];
	sprintf(str2, "%d", _vertsCount);
	vertsWords += str2;

	GLfloat baseX = 10;
	GLfloat baseY = 10;
	int count = 0;

	for (auto it = drawCallWords.begin(); it != drawCallWords.end(); ++it) {
		std::string temp;
		temp.push_back(*it);
		CharacterInfo* c = FontCache::getInstance()->getCharacterInfo("Res/Fonts/msyh.ttc", temp, 40, false, 0);
		V3F_C4B_T2F lb, rb, rt, lt;
		lb.setVertices(baseX + c->getBearing().x, baseY + c->getBearing().y - c->getSize().y, 0);
		lb.setColor(255, 255, 255, 255);
		lb.setUV(c->getSpriteFrame()->getLBTexCoord().x, c->getSpriteFrame()->getLBTexCoord().y);
		rb.setVertices(baseX + c->getBearing().x + c->getSize().x, baseY + c->getBearing().y - c->getSize().y, 0);
		rb.setColor(255, 255, 255, 255);
		rb.setUV(c->getSpriteFrame()->getRBTexCoord().x, c->getSpriteFrame()->getRBTexCoord().y);
		rt.setVertices(baseX + c->getBearing().x + c->getSize().x, baseY + c->getBearing().y, 0);
		rt.setColor(255, 255, 255, 255);
		rt.setUV(c->getSpriteFrame()->getRTTexCoord().x, c->getSpriteFrame()->getRTTexCoord().y);
		lt.setVertices(baseX + c->getBearing().x, baseY + c->getBearing().y, 0);
		lt.setColor(255, 255, 255, 255);
		lt.setUV(c->getSpriteFrame()->getLTTexCoord().x, c->getSpriteFrame()->getLTTexCoord().y);
		_polyInfo.pushVert(lb);
		_polyInfo.pushVert(rb);
		_polyInfo.pushVert(rt);
		_polyInfo.pushVert(lt);
		_polyInfo.pushIndices(count * 4);
		_polyInfo.pushIndices(count * 4 + 1);
		_polyInfo.pushIndices(count * 4 + 3);
		_polyInfo.pushIndices(count * 4 + 1);
		_polyInfo.pushIndices(count * 4 + 2);
		_polyInfo.pushIndices(count * 4 + 3);
		++count;

		baseX += c->getAdvance() >> 6;
	}

	baseX = 10;
	baseY = 60;

	for (auto it = vertsWords.begin(); it != vertsWords.end(); ++it) {
		std::string temp;
		temp.push_back(*it);
		CharacterInfo* c = FontCache::getInstance()->getCharacterInfo("Res/Fonts/msyh.ttc", temp, 40, false, 0);
		V3F_C4B_T2F lb, rb, rt, lt;
		lb.setVertices(baseX + c->getBearing().x, baseY + c->getBearing().y - c->getSize().y, 0);
		lb.setColor(255, 255, 255, 255);
		lb.setUV(c->getSpriteFrame()->getLBTexCoord().x, c->getSpriteFrame()->getLBTexCoord().y);
		rb.setVertices(baseX + c->getBearing().x + c->getSize().x, baseY + c->getBearing().y - c->getSize().y, 0);
		rb.setColor(255, 255, 255, 255);
		rb.setUV(c->getSpriteFrame()->getRBTexCoord().x, c->getSpriteFrame()->getRBTexCoord().y);
		rt.setVertices(baseX + c->getBearing().x + c->getSize().x, baseY + c->getBearing().y, 0);
		rt.setColor(255, 255, 255, 255);
		rt.setUV(c->getSpriteFrame()->getRTTexCoord().x, c->getSpriteFrame()->getRTTexCoord().y);
		lt.setVertices(baseX + c->getBearing().x, baseY + c->getBearing().y, 0);
		lt.setColor(255, 255, 255, 255);
		lt.setUV(c->getSpriteFrame()->getLTTexCoord().x, c->getSpriteFrame()->getLTTexCoord().y);
		_polyInfo.pushVert(lb);
		_polyInfo.pushVert(rb);
		_polyInfo.pushVert(rt);
		_polyInfo.pushVert(lt);
		_polyInfo.pushIndices(count * 4);
		_polyInfo.pushIndices(count * 4 + 1);
		_polyInfo.pushIndices(count * 4 + 3);
		_polyInfo.pushIndices(count * 4 + 1);
		_polyInfo.pushIndices(count * 4 + 2);
		_polyInfo.pushIndices(count * 4 + 3);
		++count;

		baseX += c->getAdvance() >> 6;
	}
	
	//LX_LOG("%s\n%s\n", drawCallWords.c_str(), vertsWords.c_str());
	
	if (_vao == 0) {
		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);
		glGenBuffers(1, &_ebo);
		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_C4B_T2F) * _polyInfo.getVertsCount(), _polyInfo.getVerts(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _polyInfo.getIndicesCount(), _polyInfo.getIndices(), GL_DYNAMIC_DRAW);
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
		glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_C4B_T2F) * _polyInfo.getVertsCount(), _polyInfo.getVerts(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _polyInfo.getIndicesCount(), _polyInfo.getIndices(), GL_DYNAMIC_DRAW);
		glBindVertexArray(0);
	}

	glActiveTexture(GL_TEXTURE0);
	TextureGridCache::getInstance()->getFontsGrid()->bind();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	_shader->use();
	_shader->updateBuiltinUniforms(glm::mat4());
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _polyInfo.getIndicesCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

