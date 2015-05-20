#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"

class SettingLayer : public cocos2d::LayerColor
{
public:
	SettingLayer(void);
	virtual ~SettingLayer(void);
	CREATE_FUNC(SettingLayer);

	virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	void onErase(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onReset(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onAudio(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onExit(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onDecr(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onIncr(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

private:
	bool _audioStatus;
	cocos2d::Image *_colorImage;
	cocos2d::Sprite *_colorPicker;
	cocos2d::ui::Button *_audioButton;
};

