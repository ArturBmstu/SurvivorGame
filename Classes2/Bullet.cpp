#include "Bullet.h"
#include "math\CCMath.h"

Bullet* Bullet::createBullet(Layer* layer)
{
	Bullet *ret = new (std::nothrow) Bullet();
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	layer->addChild(ret);
	return ret;
}

bool Bullet::init() {
	if (!ParticleMeteor::init())
		return false;

	setStartSize(8);
	setStartSizeVar(0);
	setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);
	setPositionType(ParticleSystem::PositionType::GROUPED);
	setGravity(Vec2::ZERO);
	setAngleVar(0);
	setSpeed(0);
	setSpeedVar(0);
	setLife(2);
	setLifeVar(0);
	setStartColor(Color4F::RED);
	setEndColor(Color4F::RED);

	return true;
}

void Bullet::setPosAndPhysics(Vec2 pos, float angleInDegrees) {
	setPosition(pos);
	setAngle(angleInDegrees);

	auto ph = PhysicsBody::createCircle(getContentSize().width);
	Vec2 velocityNormalized;
	velocityNormalized = velocityNormalized.forAngle(CC_DEGREES_TO_RADIANS(angleInDegrees));
	ph->setVelocity(DEF_BULLET_VELOCITY * velocityNormalized);
	addComponent(ph);
}