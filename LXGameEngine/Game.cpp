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
#include "LabelSprite.h"
#include "Label.h"
#include "ParticleEmitter.h"

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
	auto sceneeeee = Scene::getInstance();
	sceneeeee->scheduleUpdate(1.0, 1, [](float dt) {
		ParticleEmitter* pe = new ParticleEmitter();
		pe->initWithPlist("Res/Particle/firework.plist");
		pe->setPosition(200, 200);
		pe->autoRelease();
		/*pe->scheduleUpdate(0.015, -1, [pe](float dt) {
			pe->setPosition(pe->getPosition().x + 1.0, pe->getPosition().y);
		});*/

		ParticleEmitter* pe2 = new ParticleEmitter();
		pe2->initWithPlist("Res/Particle/fire.plist");
		pe2->setPosition(500, 200);
		pe2->autoRelease();

		ParticleEmitter* pe3 = new ParticleEmitter();
		pe3->initWithPlist("Res/Particle/smoke.plist");
		pe3->setPosition(800, 200);
		pe3->autoRelease();

		auto scene = Scene::getInstance();
		scene->addChild(pe);
		scene->addChild(pe2);
		scene->addChild(pe3);
	});
	return true;
}


//bool Game::start() {
//	//freetype
//	auto ins = FontCache::getInstance();
//	ins->getFaceWithKey("Res/Fonts/arial.ttf");
//	LX_LOG("Hash %d\n", ins->getHash("nihaoa", "a", 23, true, 2));
//	LX_LOG("Hash %d\n", ins->getHash("nihaoa", "a", 23, false, 3));
//	LX_LOG("Hash %d\n", ins->getHash("nihaoa", "a", 23, false, 2));
//	////CharacterInfo* charInfo = ins->getCharacterInfo("Res/Fonts/arial.ttf", "a", 48, false, 2);
//	////charInfo->dump();
//	LabelSprite* labelSprite = new LabelSprite();
//	labelSprite->initWithString("Res/Fonts/arial.ttf", "a", 30, true, 1);
//	labelSprite->setPosition(800, 500);
//	labelSprite->setScale(1, 1);
//	labelSprite->setColor(255, 0, 0);
//	////LX_LOG("contentSize, %f, %f\n", labelSprite->getContentSize().x, labelSprite->getContentSize().y);
//	//LabelSprite* labelSprite2 = new LabelSprite();
//	//labelSprite2->initWithString("Res/Fonts/arial.ttf", "B", 40, false, 0);
//	//labelSprite2->setPosition(600, 500);
//	//labelSprite2->setScale(1, 1);
//	//labelSprite2->setColor(255, 255, 0);
//
//	auto scene = Scene::getInstance();
//	scene->addChild(labelSprite);
//	// scene->addChild(labelSprite2);
//
//	Label* lbl = new Label();
//	scene->addChild(lbl);
//	lbl->initWithFont("Res/Fonts/arial.ttf", 56, "abcdefghijklmnopqrstuvwxyz");
//	lbl->setPosition(300, 300);
//	lbl->setColor(255, 0, 0);
//	lbl->setOpacity(255);
//	//lbl->setScale(5, 3);
//	//lbl->setRotation(30);
//	lbl->setOutlineSize(2);
//	lbl->setOutlineColor(0, 255, 0);
//
//	//lbl->setString("aeiou");
//
//	Button* btn = new (std::nothrow) Button();
//	btn->initWithFile("Res/jvren.png");
//	btn->setCallback([lbl](int x, int y) {lbl->setString(lbl->getString() + "123"); lbl->setOpacity(100); });
//	scene->addChild(btn);
//
//	lbl->scheduleUpdate(5.0, 1, [lbl](float dt) {lbl->setString(lbl->getString() + "123"); });
//
//	//// Create fontchar map
//	//Texture2D* texture = new Texutre2D();
//	//SpriteFrame* spriteFrame = new SpriteFrame();
//	//spriteFrame->initWithTextureRect(TextureGridCache::getInstance()->getFontsGrid()->get);
//	//Sprite* sprite = new Sprite();
//	//sprite->init
//	
//	return true;
//}

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
