#include "SettingLayer.h"
#include "BoardScene.h"

USING_NS_CC;

// for ui layout button
using namespace cocos2d::ui;

SettingLayer::SettingLayer(void)
{
}


SettingLayer::~SettingLayer(void)
{
}


bool SettingLayer::init()
{
	// ��ʼ�����ò�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255),	220, 220))
		return false;

	// ���ô���ģʽ
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	// ��Ӳ�ɫ��
	_colorPicker = Sprite::create("ColorPicker.png");
	_colorPicker->setPosition(_colorPicker->getContentSize().width / 2, _colorPicker->getContentSize().height / 2);
	this->addChild(_colorPicker);

	_colorImage = new Image();
	_colorImage->initWithImageFile("ColorPicker.png");

	// ��Ӱ�ť����
	auto *layout = Layout::create();
	layout->setLayoutType(Layout::Type::VERTICAL);
	layout->setPosition(Vec2(_colorPicker->getContentSize().width, 0));
	layout->setContentSize(Size(100, _colorPicker->getContentSize().width));
	this->addChild(layout);

	// ���������߿�ť
	Button *incrButton = Button::create("ButtonNormal.png", "ButtonSelected.png");
	incrButton->addTouchEventListener(CC_CALLBACK_2(SettingLayer::onIncr, this));
	incrButton->setTitleText("Incr");
	layout->addChild(incrButton);

	// ���Ӽ����߿�ť
	Button *decrButton = Button::create("ButtonNormal.png", "ButtonSelected.png");
	decrButton->addTouchEventListener(CC_CALLBACK_2(SettingLayer::onDecr, this));
	decrButton->setTitleText("Decr");
	layout->addChild(decrButton);

	// �����˳���ť
	Button *exitButton = Button::create("ButtonNormal.png", "ButtonSelected.png");
	exitButton->addTouchEventListener(CC_CALLBACK_2(SettingLayer::onExit, this));
	exitButton->setTitleText("Exit");
	layout->addChild(exitButton);

	// �������ְ�ť
	_audioButton = Button::create("ButtonNormal.png", "ButtonSelected.png");
	_audioButton->addTouchEventListener(CC_CALLBACK_2(SettingLayer::onAudio, this));
	_audioButton->setTitleText("Stop");
	layout->addChild(_audioButton);
	_audioStatus = true;

	// �������ð�ť
	Button *resetButton = Button::create("ButtonNormal.png", "ButtonSelected.png");
	resetButton->addTouchEventListener(CC_CALLBACK_2(SettingLayer::onReset, this));
	resetButton->setTitleText("Reset");
	layout->addChild(resetButton);

	// ���Ӳ�����ť
	Button *eraseButton = Button::create("ButtonNormal.png", "ButtonSelected.png");
	eraseButton->addTouchEventListener(CC_CALLBACK_2(SettingLayer::onErase, this));
	eraseButton->setTitleText("Erase");
	layout->addChild(eraseButton);

	return true;
}


bool SettingLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	Point location = touch->getLocation();
	if (_colorPicker->getBoundingBox().containsPoint(location)) {
		unsigned char *data = _colorImage->getData();
		unsigned int *pixel = (unsigned int *)data;
		pixel = pixel + (220 * (unsigned int)(220 - location.y)) + (unsigned int)location.x;
		BoardScene *runingScene = (BoardScene *)Director::getInstance()->getRunningScene();
		runingScene->setColor(*pixel);
		return true;
	}

	return false;
}


void SettingLayer::onErase(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED) return ;

	BoardScene *runingScene = (BoardScene *)Director::getInstance()->getRunningScene();
	runingScene->eraseDraw();
}


void SettingLayer::onReset(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED) return ;

	BoardScene *runingScene = (BoardScene *)Director::getInstance()->getRunningScene();
	runingScene->clearDraw();
}


void SettingLayer::onAudio(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED) return ;

	BoardScene *runingScene = (BoardScene *)Director::getInstance()->getRunningScene();
	if (_audioStatus) {
		_audioStatus = false;
		runingScene->stopAudio();
		_audioButton->setTitleText("Play");
	} else {
		_audioStatus = true;
		runingScene->playAudio();
		_audioButton->setTitleText("Stop");
	}
}


void SettingLayer::onExit(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED) return ;

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void SettingLayer::onDecr(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED) return ;

	BoardScene *runingScene = (BoardScene *)Director::getInstance()->getRunningScene();
	runingScene->decrDraw();
}


void SettingLayer::onIncr(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED) return ;

	BoardScene *runingScene = (BoardScene *)Director::getInstance()->getRunningScene();
	runingScene->incrDraw();
}
