#include "DynamicEntity.h"
#include "Gambler.h"

void DynamicEntity::rotateTo(float dstAngle) {
	runAction(RotateTo::create(ROTATE_DURATION, dstAngle));
	//setRotation(dstAngle);
}

void DynamicEntity::setVelocity(Vec2 velocity) {
	_velocity = velocity;
	physicsBody->setVelocity(velocity);
}

Vec2 DynamicEntity::getVelocity() {
	return _velocity;
}

Layer* DynamicEntity::getLayer() {
	return _layer;
}