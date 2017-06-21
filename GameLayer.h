#pragma once
#include "cocos2d.h"
#include "Gambler.h"
#include "Player.h"
#include "Constants.h"
#include "LevelMap.h"
USING_NS_CC;

class GameLayer : public Layer {
public:
	static Scene* createScene();
	virtual bool init();

	void Play(Ref* pSender);
	CREATE_FUNC(GameLayer);
	SpriteFrameCache* cacher;

protected:
	PhysicsWorld* physicsWorld;
	Scene* scene;

private:
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	std::list<int> moveKeysPressed;

	bool onContactBegin(PhysicsContact& contact);
	bool onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve);
	bool onContactPostSolve(PhysicsContact& contact);
	bool onContactSeparate(PhysicsContact& contact);

	Player* player;
	LevelMap* level;
};
