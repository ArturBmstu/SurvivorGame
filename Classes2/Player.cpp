#include "Player.h"

Player::Player(std::string name, Layer* layer) :
	Gambler(layer)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	initializeSpriteFrames(name);
	
	if (name == "survivor")
		setScale(SURVIVOR_SCALE);
	setPosition(Vec2(origin.x + getContentSize().width / 2, origin.y + getContentSize().height / 2));

	setTag(PLAYER_TAG);
	// Physics settings
	physicsBody = PhysicsBody::createCircle(getContentSize().height/3, PhysicsMaterial(1.0f, 0.0f, 0.0f));
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	physicsBody->setRotationEnable(false);
	
	//physicsBody->setGroup(3);
	addComponent(physicsBody);

	layer->addChild(this);

	scheduleUpdate();
	resume();
}

void Player::initializeSpriteFrames(std::string name) {
	initSpriteFrames(flashlightIdle, name + FLASH_IDLE);
	initSpriteFrames(flashlightMelee, name + FLASH_MELEE);
	initSpriteFrames(flashlightMove, name + FLASH_MOVE);

	initSpriteFrames(knifeIdle, name + KNIFE_IDLE);
	initSpriteFrames(knifeMelee, name + KNIFE_MELEE);
	initSpriteFrames(knifeMove, name + KNIFE_MOVE);

	initSpriteFrames(handgunIdle, name + HANDGUN_IDLE);
	initSpriteFrames(handgunMelee, name + HANDGUN_MELEE);
	initSpriteFrames(handgunMove, name + HANDGUN_MOVE);
	initSpriteFrames(handgunReload, name + HANDGUN_RELOAD);
	initSpriteFrames(handgunShoot, name + HANDGUN_SHOOT);

	initSpriteFrames(rifleIdle, name + RIFLE_IDLE);
	initSpriteFrames(rifleMelee, name + RIFLE_MELEE);
	initSpriteFrames(rifleMove, name + RIFLE_MOVE);
	initSpriteFrames(rifleReload, name + RIFLE_RELOAD);
	initSpriteFrames(rifleShoot, name + RIFLE_SHOOT);

	initSpriteFrames(shotgunIdle, name + SHOTGUN_IDLE);
	initSpriteFrames(shotgunMelee, name + SHOTGUN_MELEE);
	initSpriteFrames(shotgunMove, name + SHOTGUN_MOVE);
	initSpriteFrames(shotgunReload, name + SHOTGUN_RELOAD);
	initSpriteFrames(shotgunShoot, name + SHOTGUN_SHOOT);

	initWithSpriteFrameName(name + SHOTGUN_IDLE + "_0.png");
	currentIdleFrames = rifleIdle;
	currentMeleeFrames = rifleMelee;
	currentMoveFrames = rifleMove;
	currentShootFrames = rifleShoot;
	currentReloadFrames = rifleReload;
	animate(currentIdleFrames);
}

void Player::runUp() {
	animate(currentMoveFrames);
	Gambler::runUp();
	lastVelocity = getVelocity();
}

void Player::runRightUp() {
	animate(currentMoveFrames);
	Gambler::runRightUp();
	lastVelocity = getVelocity();
}

void Player::runRight() {
	animate(currentMoveFrames);
	Gambler::runRight();
	lastVelocity = getVelocity();
}

void Player::runRightDown() {
	animate(currentMoveFrames);
	Gambler::runRightDown();
	lastVelocity = getVelocity();
}

void Player::runDown() {
	animate(currentMoveFrames);
	Gambler::runDown();
	lastVelocity = getVelocity();
}

void Player::runLeftDown() {
	animate(currentMoveFrames);
	Gambler::runLeftDown();
	lastVelocity = getVelocity();
}

void Player::runLeft() {
	animate(currentMoveFrames);
	Gambler::runLeft();
	lastVelocity = getVelocity();
}

void Player::runLeftUp() {
	animate(currentMoveFrames);
	Gambler::runLeftUp();
	lastVelocity = getVelocity();
}

void Player::stop() {
	animate(currentIdleFrames);
	Gambler::stop();
}

void Player::shoot() {
	if (!currentShootFrames.empty())
		animate(currentShootFrames);
	else
		animate(shotgunShoot);
	setShootingEnabled(true);
}

bool Player::isShootingEnabled() {
	return _isShooting;
}

void Player::setShootingEnabled(bool enabled) {
	_isShooting = enabled;
}

void Player::update(float delta) {
	if (!isShootingEnabled())
		return;
	Vec2 bulletPos;
	float rotationInDegrees = -getRotation();
	float rotation = CC_DEGREES_TO_RADIANS(rotationInDegrees);
	bulletPos.x = getPosition().x + getContentSize().width * cos(rotation) * SURVIVOR_SCALE / 2 + getContentSize().height * SURVIVOR_SCALE * sin(rotation) / 4.7;
	bulletPos.y = getPosition().y + getContentSize().width * sin(rotation) * SURVIVOR_SCALE / 2 - getContentSize().height * SURVIVOR_SCALE * cos(rotation) / 4.7;

	auto bullet = Bullet::createBullet(getLayer());
	bullet->setPosAndPhysics(bulletPos, rotationInDegrees);

	setShootingEnabled(false);
}