#include "BoardLayer.h"
#include "BoardScene.h"

USING_NS_CC;

BoardLayer::BoardLayer()
{
}


BoardLayer::~BoardLayer()
{
}


bool BoardLayer::init()
{
	// 初始化绘画层
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255), visibleSize.width, visibleSize.height))
		return false;

	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	this->setTouchEnabled(true);

	// 创建DrawNode
	_drawNode = DrawNode::create();
	this->addChild(_drawNode);

	_drawColor = Color4F(1, 0, 0, 1);
	_oldColor = Color4F(1, 0, 0, 1);
	_drawSize = 1;

	// 消除锯齿
// 	glEnable(GL_LINE_SMOOTH);
// 	glEnable(GL_POINT_SMOOTH);

	return true;
}


bool BoardLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	BoardScene *runingScene = (BoardScene *)Director::getInstance()->getRunningScene();
	if (runingScene->hideSetting()) return false;

	_originPoint = touch->getLocation();
	return true;
}


void BoardLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	Point location = touch->getLocation();
	
	_drawNode->drawSegment(_originPoint, location, _drawSize, _drawColor);
	_originPoint = location;
}


void BoardLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if (_originPoint == touch->getLocation())
		_drawNode->drawSolidCircle(_originPoint, _drawSize, CC_DEGREES_TO_RADIANS(0), 30, _drawColor);
}


void BoardLayer::eraseDraw(void)
{
	_oldColor = _drawColor;
	_drawColor = Color4F(1, 1, 1, 1);
}


bool BoardLayer::resumeDraw(void)
{
	if (_drawColor == Color4F(1, 1, 1, 1)) {
		_drawColor = _oldColor;
		return true;
	}

	return false;
}


void BoardLayer::setColor(unsigned int color)
{
	GLubyte r = color & 0xff;
	GLubyte g = (color >> 8) & 0xff;
	GLubyte b = (color >> 16) & 0xff;
	GLubyte a = (color >> 24) & 0xff;
	_drawColor = Color4F(Color4B(r, g, b, a));
}
