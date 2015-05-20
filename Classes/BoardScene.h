#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"

class BoardLayer;
class SettingLayer;
class BoardScene : public cocos2d::Scene
{
public:
	BoardScene();
	virtual ~BoardScene();
	CREATE_FUNC(BoardScene);

	virtual bool init();

	void onSetting(void);
	void playAudio(void);
	void stopAudio(void);
	bool hideSetting(void);
	void eraseDraw(void);
	void clearDraw(void);
	void incrDraw(void);
	void decrDraw(void);

	void setColor(unsigned int color);

private:
	int _audioID;
	BoardLayer *_boardLayer;
	SettingLayer *_settingLayer;
};

