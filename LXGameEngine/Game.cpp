#include "stdafx.h"
#include "Game.h"
#include "Scene.h"
#include "Sprite.h"
#include "Button.h"
#include "Director.h"
#include "TextureCache.h"
#include "SpriteFrameCache.h"
#include "TextureGrid.h"
#include "TextureGridCache.h"
#include "FontCache.h"

Game * g_Game = nullptr;

Game::Game()
{
}

Game * Game::getInstance()
{
	if (g_Game == nullptr)
		g_Game = new (std::nothrow) Game;
	return g_Game;
}


bool Game::start() {
	//freetype
	auto ins = FontCache::getInstance();
	ins->getFaceWithKey("123a.ttf");
	return true;
}

//bool Game::start()
//{
//	//common tests
//	auto scene = Scene::getInstance();
//
//	// Create textureGrids
//	auto insTGC = TextureGridCache::getInstance();
//	insTGC->addTextureGridWithKey("test_texture_grid", 2048, 2048, 512, 512);
//	insTGC->enableTextureGridWithKey("test_texture_grid");
//
//	Button* sprite = new (std::nothrow) Button();
//	sprite->initWithFile("Res/jvren.png");
//	// sprite->initWithFile("Res/test.png");
//	// insTGC->disableTextureGridCache();
//	sprite->setCallback([sprite](int x, int y) {
//		//LX_LOG("Button::%d, %d\n", x, y);
//		glm::vec2& np = sprite->convertToNodeSpace(x, y);
//		//LX_LOG("NodeSpace::%f, %f\n", np.x, np.y);
//		Sprite* s = new Sprite();
//		s->initWithFile("Res/test.png");
//		s->setContentSize(20, 20);
//		s->setPosition(np.x, np.y);
//		sprite->addChild(s);
//		auto fps = Director::getInstance()->getFPS();
//		if (fps == 30) {
//			Director::getInstance()->setFPS(60);
//		}
//		else {
//			Director::getInstance()->setFPS(30);
//		}
//		//sprite->getParent()->removeChild(sprite);
//	});
//	sprite->scheduleUpdate(1.0f, 5, [](float dt) {
//		int cnt1 = SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
//		int cnt2 = TextureCache::getInstance()->removeUnusedTextures();
//		LX_LOG("RemoveUnusedSpriteFrames: %d\n", cnt1);
//		LX_LOG("RemoveUnusedTextures: %d\n", cnt2);
//	});
//	//sprite->dump();
//	sprite->setContentSize(512, 512);
//	sprite->setPosition(512.0, 512.0f);
//	sprite->setAnchorPoint(0.5f, 0.5f);
//	sprite->setSwallowTouches(true);
//	sprite->autoRelease();
//	//sprite->setRotation(-45.0f);
//	//sprite->setScale(1.0f, 2.0f);
//	//sprite->visit(glm::mat4());
//	scene->addChild(sprite);
//
//	Sprite* sprite2 = new (std::nothrow) Sprite();
//	sprite2->initWithFile("Res/test.png");
//	sprite2->setPosition(0, 0);
//	sprite2->setContentSize(512, 512);
//	sprite2->autoRelease();
//	sprite2->setLocalZ(-1);
//	sprite->addChild(sprite2);
//	sprite->removeChild(sprite2);
//
//	Sprite* sprite3 = new (std::nothrow) Sprite();
//	sprite3->initWithFile("Res/test.png");
//	sprite3->setPosition(-512, -512);
//	sprite3->setContentSize(512, 512);
//	sprite3->setColor(0, 255, 0);
//	sprite3->setOpacity(100);
//	sprite3->autoRelease();
//	sprite3->setLocalZ(1);
//	sprite->addChild(sprite3);
//	sprite->removeChild(sprite3);
//
//	int cnt1 = SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
//	int cnt2 = TextureCache::getInstance()->removeUnusedTextures();
//	LX_LOG("RemoveUnusedSpriteFrames: %d\n", cnt1);
//	LX_LOG("RemoveUnusedTextures: %d\n", cnt2);
//
//	//sprite->autoRelease();
//	/*Texture2D* texture = new Texture2D();
//	texture->initWithFileName("Res/wall.jpg");
//	texture->dump();
//	texture->release();
//
//	Texture2D* texture2 = new Texture2D();
//	texture2->initWithFileName("Res/wall.jpg");
//	texture2->dump();*/
//
//	/*texture->initWithFileName("Res/wall.jpg", Image::IMAGE_RGB);
//	texture->dump();*/
//	/*Shader* s = new Shader();
//	s->initWithFiles("Res\\Shaders\\default.vert", "Res\\Shaders\\default.frag");
//	s->dump();*/
//
//	//glCreateShader(GL_VERTEX_SHADER);
//	/*Shader* shader = ShaderCache::getInstance()->getGlobalShader(ShaderCache::LX_SHADERS_PVM_DEFAULT);
//	shader->dump();*/
//
//
//	return true;
//
//}

bool Game::loop()
{
	return true;
}


Game::~Game()
{
}
