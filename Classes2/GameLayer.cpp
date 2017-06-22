#include "GameLayer.h"

const int keyW = static_cast<int>(EventKeyboard::KeyCode::KEY_W);
const int keyD = static_cast<int>(EventKeyboard::KeyCode::KEY_D);
const int keyS = static_cast<int>(EventKeyboard::KeyCode::KEY_S);
const int keyA = static_cast<int>(EventKeyboard::KeyCode::KEY_A);

Scene* GameLayer::createScene() {
	Scene* scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	
	Layer* layer = GameLayer::create();
	scene->addChild(layer);

	return scene;
}

bool GameLayer::init() {
	if (!Layer::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto menuItem1 = MenuItemFont::create("Play", CC_CALLBACK_1(GameLayer::Play, this));
	Size menuItem1Size = menuItem1->getContentSize();
	menuItem1->setPosition(Vec2(visibleSize.width/2 - menuItem1Size.width/2, visibleSize.height/2 - menuItem1Size.height/2));

	Menu* menu = Menu::create(menuItem1, nullptr);
	menu->setPosition(Vec2(0, 0)); // Try without it
	this->addChild(menu);

	return true;
}

void GameLayer::Play(Ref* pSender) {
	level = new LevelMap("map/level1.tmx", this);
	level->initFirstLevel();

	TMXTiledMap* map = level->getMap();
	addChild(map);

	auto mapSize = map->getContentSize();
	auto tileSize = map->getTileSize();

	scene = getScene();
	physicsWorld = scene->getPhysicsWorld();
	
	cacher = SpriteFrameCache::getInstance();
	cacher->addSpriteFramesWithFile("survivor/survivor.plist", "survivor/survivor.png");
	
	player = new Player("survivor", this);

	Follow* camera = Follow::create(player, Rect(0, 0, mapSize.width, mapSize.height));
	camera->retain();
	runAction(camera);

	auto listener = EventListenerKeyboard::create();
	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
	listener->onKeyPressed = CC_CALLBACK_2(GameLayer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	/* Deprecated. Not recommended */
	//setKeyboardEnabled(true);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_2(GameLayer::onContactPreSolve, this);
	contactListener->onContactPostSolve = CC_CALLBACK_1(GameLayer::onContactPostSolve, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(GameLayer::onContactSeparate, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	
	//scheduleUpdate();
	//resume();
}

bool GameLayer::onContactBegin(PhysicsContact& contact) {
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	/*if (nodeA->getTag() == BULLET_TAG && nodeB->getTag() == LAKE_TAG)
		return false;

	if (nodeB->getTag() == BULLET_TAG && nodeA->getTag() == LAKE_TAG)
		return false;*/
	if (nodeA->getTag() == BULLET_TAG) {
		if (nodeB->getTag() == LAKE_TAG)
			return false;
		if (nodeB->getTag() == BOX_TAG) {
			nodeB->getPhysicsBody()->setVelocity(Vec2(0, 0));
			nodeB->getPhysicsBody()->setAngularVelocity(0);
		}
		Bullet* bullet = dynamic_cast<Bullet*>(nodeA);
		bullet->setDuration(0);
		bullet->setLife(1);
		bullet->setLifeVar(0);
		bullet->removeComponent(bullet->getPhysicsBody());
		bullet->removeFromParentAndCleanup(true);
		return false;
	}
	if (nodeB->getTag() == BULLET_TAG) {
		if (nodeA->getTag() == LAKE_TAG)
			return false;
		if (nodeA->getTag() == BOX_TAG) {
			nodeA->getPhysicsBody()->setVelocity(Vec2(0, 0));
			nodeA->getPhysicsBody()->setAngularVelocity(0);
		}
		Bullet* bullet = dynamic_cast<Bullet*>(nodeA);
		bullet->setDuration(0);
		bullet->setLife(1);
		bullet->setLifeVar(0);
		bullet->removeComponent(bullet->getPhysicsBody());
		bullet->removeFromParentAndCleanup(true);
		return false;
	}
	return true;
}

bool GameLayer::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve) {
	return true;
}

bool GameLayer::onContactPostSolve(PhysicsContact& contact) {
	return true;
}

bool GameLayer::onContactSeparate(PhysicsContact& contact) {
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	auto nodeA = bodyA->getNode();
	auto nodeB = bodyB->getNode();

	if (!nodeA)
		return true;

	if (nodeA->getTag() == PLAYER_TAG) {
		Gambler* gambler = dynamic_cast<Gambler*>(nodeA);
		gambler->getPhysicsBody()->setVelocity(gambler->getVelocity());
	}
	else if (nodeA->getTag() == BULLET_TAG) {
		if (nodeB->getTag() == LAKE_TAG)
			return false;
		Bullet* bullet = dynamic_cast<Bullet*>(nodeA);
		bullet->setDuration(0);
		bullet->setLife(1);
		bullet->setLifeVar(0);
		bullet->removeComponent(bullet->getPhysicsBody());
		bullet->removeFromParentAndCleanup(true);
	}
	else {
		bodyA->setVelocity(Vec2(0, 0));
		bodyA->setAngularVelocity(0);
	}

	if (!nodeB)
		return true;

	if (nodeB->getTag() == PLAYER_TAG) {
		Gambler* gambler = dynamic_cast<Gambler*>(nodeB);
		gambler->getPhysicsBody()->setVelocity(gambler->getVelocity());
	}
	else if (nodeB->getTag() == BULLET_TAG) {
		if (nodeA->getTag() == LAKE_TAG)
			return false;
		Bullet* bullet = dynamic_cast<Bullet*>(nodeB);
		bullet->setDuration(0);
		bullet->setLife(1);
		bullet->setLifeVar(1);
		bullet->removeComponent(bullet->getPhysicsBody());
		bullet->removeFromParentAndCleanup(true);
		
	}
	else {
		bodyB->setVelocity(Vec2(0, 0));
		bodyB->setAngularVelocity(0);
	}

	return true;
}

void GameLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	int keyCodeInt = static_cast<int> (keyCode);
	switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_W:
			if (!moveKeysPressed.empty()) {
				if (moveKeysPressed.back() == keyA)
					player->runLeftUp();
				else if (moveKeysPressed.back() == keyD)
					player->runRightUp();
			}
			else
				player->runUp();
			moveKeysPressed.push_back(keyCodeInt);
			break;
		case EventKeyboard::KeyCode::KEY_D:
			if (!moveKeysPressed.empty()) {
				if (moveKeysPressed.back() == keyW)
					player->runRightUp();
				else if (moveKeysPressed.back() == keyS)
					player->runRightDown();
			}
			else
				player->runRight();
			moveKeysPressed.push_back(keyCodeInt);
			break;
		case EventKeyboard::KeyCode::KEY_S:
			if (!moveKeysPressed.empty()) {
				if (moveKeysPressed.back() == keyA)
					player->runLeftDown();
				else if (moveKeysPressed.back() == keyD)
					player->runRightDown();
			}
			else
				player->runDown();
			moveKeysPressed.push_back(keyCodeInt);
			break;
		case EventKeyboard::KeyCode::KEY_A:
			if (!moveKeysPressed.empty()) {
				if (moveKeysPressed.back() == keyW)
					player->runLeftUp();
				else if (moveKeysPressed.back() == keyS)
					player->runLeftDown();
			}
			else
				player->runLeft();
			moveKeysPressed.push_back(keyCodeInt);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			player->shoot();
			break;
	}
}

void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_SPACE:
			player->setShootingEnabled(false);
			break;
	}
	int keyCodeInt = static_cast<int> (keyCode);
	moveKeysPressed.remove(keyCodeInt);
	if (!moveKeysPressed.empty()) {
		int keyCurrent = moveKeysPressed.back();
		moveKeysPressed.pop_back();
		switch (keyCurrent) {
			case keyW:
				if (!moveKeysPressed.empty()) {
					int keyPrev = moveKeysPressed.back();
					moveKeysPressed.push_back(keyCurrent);
					if (keyPrev == keyD)
						player->runRightUp();
					else if (keyPrev == keyA)
						player->runLeftUp();
				}
				else {
					moveKeysPressed.push_back(keyCurrent);
					player->runUp();
				}
				break;
			case keyD:
				if (!moveKeysPressed.empty()) {
					int keyPrev = moveKeysPressed.back();
					moveKeysPressed.push_back(keyCurrent);
					if (keyPrev == keyW)
						player->runRightUp();
					else if (keyPrev == keyS)
						player->runRightDown();
				}
				else {
					moveKeysPressed.push_back(keyCurrent);
					player->runRight();
				}
				break;
			case keyS:
				if (!moveKeysPressed.empty()) {
					int keyPrev = moveKeysPressed.back();
					moveKeysPressed.push_back(keyCurrent);
					if (keyPrev == keyD)
						player->runRightDown();
					else if (keyPrev == keyA)
						player->runLeftDown();
				}
				else {
					moveKeysPressed.push_back(keyCurrent);
					player->runDown();
				}
				break;
			case keyA:
				if (!moveKeysPressed.empty()) {
					int keyPrev = moveKeysPressed.back();
					moveKeysPressed.push_back(keyCurrent);
					if (keyPrev == keyW)
						player->runLeftUp();
					else if (keyPrev == keyS)
						player->runLeftDown();
				}
				else  {
					moveKeysPressed.push_back(keyCurrent);
					player->runLeft();
				}
				break;
		}
	}
	else
		player->stop();
}