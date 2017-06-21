#pragma once
#include "cocos2d.h"
#include "Constants.h"
#include "DynamicEntity.h"
USING_NS_CC;

class Gambler : public DynamicEntity {
public:
	Gambler(Layer* layer);
	void initSpriteFrames(Vector<SpriteFrame*>& frames, std::string namePattern);
	void animate(Vector<SpriteFrame*>& frames, float delay=ANIM_DELAY, bool forever=true);

	virtual void runUp();
	virtual void runRightUp();
	virtual void runRight();
	virtual void runRightDown();
	virtual void runDown();
	virtual void runLeftDown();
	virtual void runLeft();
	virtual void runLeftUp();
	virtual void stop();
	virtual void shoot() {};
protected:
	SpriteFrameCache* cacher;
};
