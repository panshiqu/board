#pragma once
#include "cocos2d.h"

class BoardLayer : public cocos2d::LayerColor
{
public:
	BoardLayer();
	virtual ~BoardLayer();
	CREATE_FUNC(BoardLayer);

	virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	void clearDraw(void)	{ _drawNode->clear(); }
	void incrDraw(void)		{ if (_drawSize < 10) _drawSize++; }
	void decrDraw(void)		{ if (_drawSize > 1) _drawSize--; }

	void eraseDraw(void);
	bool resumeDraw(void);
	void setColor(unsigned int color);

private:
	cocos2d::Point _originPoint;
	cocos2d::DrawNode* _drawNode;
	cocos2d::Color4F _drawColor;
	cocos2d::Color4F _oldColor;
	float _drawSize;
};

