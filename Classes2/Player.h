#include "cocos2d.h"
#include "Constants.h"
#include "Gambler.h"
#include "DynamicEntity.h"
#include "Bullet.h"
USING_NS_CC;

class Player : public Gambler {
public:
	Player(std::string name, Layer* _layer);

	void runUp();
	using Gambler::runUp;
	void runRightUp();
	using Gambler::runRightUp;
	void runRight();
	using Gambler::runRight;
	void runRightDown();
	using Gambler::runRightDown;
	void runDown();
	using Gambler::runDown;
	void runLeftDown();
	using Gambler::runLeftDown;
	void runLeft();
	using Gambler::runLeft;
	void runLeftUp();
	using Gambler::runLeftUp;
	void stop();
	using Gambler::stop;

	void shoot();
	void update(float delta);

	bool isShootingEnabled();
	void setShootingEnabled(bool enabled=true);

	void initializeSpriteFrames(std::string name);

protected:
	Vec2 lastVelocity;

	bool _isShooting = false;

	Vector<SpriteFrame*> currentIdleFrames;
	Vector<SpriteFrame*> currentMeleeFrames;
	Vector<SpriteFrame*> currentMoveFrames;
	Vector<SpriteFrame*> currentReloadFrames;
	Vector<SpriteFrame*> currentShootFrames;

	Vector<SpriteFrame*> flashlightIdle;
	Vector<SpriteFrame*> flashlightMelee;
	Vector<SpriteFrame*> flashlightMove;

	Vector<SpriteFrame*> knifeIdle;
	Vector<SpriteFrame*> knifeMelee;
	Vector<SpriteFrame*> knifeMove;

	Vector<SpriteFrame*> handgunIdle;
	Vector<SpriteFrame*> handgunMelee;
	Vector<SpriteFrame*> handgunMove;
	Vector<SpriteFrame*> handgunReload;
	Vector<SpriteFrame*> handgunShoot;

	Vector<SpriteFrame*> rifleIdle;
	Vector<SpriteFrame*> rifleMelee;
	Vector<SpriteFrame*> rifleMove;
	Vector<SpriteFrame*> rifleReload;
	Vector<SpriteFrame*> rifleShoot;

	Vector<SpriteFrame*> shotgunIdle;
	Vector<SpriteFrame*> shotgunMelee;
	Vector<SpriteFrame*> shotgunMove;
	Vector<SpriteFrame*> shotgunReload;
	Vector<SpriteFrame*> shotgunShoot;
};