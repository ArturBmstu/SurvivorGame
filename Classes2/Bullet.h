#pragma once
#include "DynamicEntity.h"
#include "cocos2d.h"
#include "Constants.h"
USING_NS_CC;

class Bullet : public ParticleMeteor {
public:
	static Bullet* createBullet(Layer* layer);

	bool init();

	void setPosAndPhysics(Vec2 pos, float angleInDegrees);
};
