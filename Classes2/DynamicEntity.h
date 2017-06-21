#pragma once
#include "cocos2d.h"
#include "Constants.h"
USING_NS_CC;

class DynamicEntity : public Sprite {
public:
	DynamicEntity() : _velocity(Vec2(0.0f, 0.0f)) {};
	DynamicEntity(Layer* layer): _layer(layer) {};
	void rotateTo(float dstAngle);
	void setVelocity(Vec2 velocity);
	Vec2 getVelocity();

	Layer* getLayer();

protected:
	Layer* _layer;
	Vec2 _velocity;
	PhysicsBody* physicsBody;
};