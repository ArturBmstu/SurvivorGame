#include "Gambler.h"
#include "cocos2d.h"
#include "Constants.h"
#include <cmath>
#include "DynamicEntity.h"
USING_NS_CC;

Gambler::Gambler(Layer* layer) :
	DynamicEntity(layer)
{
	cacher = SpriteFrameCache::getInstance();
}

void Gambler::initSpriteFrames(Vector<SpriteFrame*>& frames, std::string namePattern) {
	if (!frames.empty())
		return;
	for (int i = 0; true; i++) {
		std::string spriteName = namePattern + "_" + std::to_string(i) + ".png";
		SpriteFrame* newFrame = cacher->getSpriteFrameByName(spriteName);
		if ( !((Sprite*) newFrame) )
			break;
		frames.pushBack(newFrame);
	}
}

void Gambler::animate(Vector<SpriteFrame*>& frames, float delay, bool forever) {
	stopAllActions();
	Animation* anim = Animation::createWithSpriteFrames(frames, delay);
	if (forever)
		runAction(RepeatForever::create(Animate::create(anim)));
	else
		runAction(Animate::create(anim));
}

void Gambler::runUp() {
	setVelocity(Vec2(0, DEF_PLAYER_VELOCITY));
	rotateTo(UP_ANGLE);
}

void Gambler::runRightUp() {
	setVelocity(Vec2(DEF_PLAYER_DIAG_VELOCITY, DEF_PLAYER_DIAG_VELOCITY));
	rotateTo(RIGHT_UP_ANGLE);
}

void Gambler::runRight() {
	setVelocity(Vec2(DEF_PLAYER_VELOCITY, 0));
	rotateTo(RIGHT_ANGLE);
}

void Gambler::runRightDown() {
	setVelocity(Vec2(DEF_PLAYER_DIAG_VELOCITY, -DEF_PLAYER_DIAG_VELOCITY));
	rotateTo(RIGHT_DOWN_ANGLE);
}

void Gambler::runDown() {
	setVelocity(Vec2(0, -DEF_PLAYER_VELOCITY));
	rotateTo(DOWN_ANGLE);
}

void Gambler::runLeftDown() {
	setVelocity(Vec2(-DEF_PLAYER_DIAG_VELOCITY, -DEF_PLAYER_DIAG_VELOCITY));
	rotateTo(LEFT_DOWN_ANGLE);
}

void Gambler::runLeft() {
	setVelocity(Vec2(-DEF_PLAYER_VELOCITY, 0));
	rotateTo(LEFT_ANGLE);
}

void Gambler::runLeftUp() {
	setVelocity(Vec2(-DEF_PLAYER_DIAG_VELOCITY, DEF_PLAYER_DIAG_VELOCITY));
	rotateTo(LEFT_UP_ANGLE);
}

void Gambler::stop() {
	setVelocity(Vec2(0, 0));
}
