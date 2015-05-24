#include "BoardScene.h"
#include "BoardLayer.h"
#include "SettingLayer.h"

USING_NS_CC;

// for audio
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

// for ui button
using namespace cocos2d::ui;

BoardScene::BoardScene()
{
}


BoardScene::~BoardScene()
{
}


bool BoardScene::init()
{
	if (!Scene::init()) return false;

	// 创建绘画层
	_boardLayer = BoardLayer::create();
	this->addChild(_boardLayer);

	// 创建设置层
	_settingLayer = SettingLayer::create();
	_settingLayer->setVisible(false);
	this->addChild(_settingLayer, 2);

	// 播放背景音乐
	_audioID = AudioEngine::play2d("background.mp3", true, 1.0f);

	// 增加设置按钮
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto settingMenu = MenuItemImage::create("SettingNormal.png", "SettingSelected.png", CC_CALLBACK_0(BoardScene::onSetting, this));
	settingMenu->setScale((visibleSize.height / 10.0f) / settingMenu->getContentSize().height);
	settingMenu->setAnchorPoint(Vec2(0.0f, 0.0f));
	auto menu = Menu::create(settingMenu, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}


void BoardScene::onSetting(void)
{
	if (!_boardLayer->resumeDraw()) {
		_settingLayer->setVisible(true);
		_settingLayer->setTouchEnabled(true);
	}
}


void BoardScene::playAudio(void)
{
	if (_audioID != AudioEngine::INVALID_AUDIO_ID)
		AudioEngine::resume(_audioID);
}


void BoardScene::stopAudio(void)
{
	if (_audioID != AudioEngine::INVALID_AUDIO_ID)
		AudioEngine::pause(_audioID);
}


bool BoardScene::hideSetting(void)
{
	if (_settingLayer->isVisible()) {
		_settingLayer->setVisible(false);
		_settingLayer->setTouchEnabled(false);
		return true;
	}

	return false;
}


void BoardScene::eraseDraw(void)
{
	hideSetting();
	_boardLayer->eraseDraw();
}


void BoardScene::clearDraw(void)
{
	hideSetting();
	_boardLayer->clearDraw();
}


void BoardScene::incrDraw(void)
{
	_boardLayer->incrDraw();
}


void BoardScene::decrDraw(void)
{
	_boardLayer->decrDraw();
}


void BoardScene::setColor(unsigned int color)
{
	_boardLayer->setColor(color);
}
