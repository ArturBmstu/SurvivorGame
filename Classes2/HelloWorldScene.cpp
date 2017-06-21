#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Gambler.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
   // this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

	auto map = TMXTiledMap::create("level2.tmx");
	addChild(map);
	//auto layer = map->getLayer("Layer0");
	//auto tile = layer->getTileAt(Vec2(1, 63));
	// add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    


	// set the appropriate resource directory for this device
	//FileUtils::getInstance()->addSearchResolutionsOrder("HD");

	// load and cache the texture and sprite frames
	auto cacher = SpriteFrameCache::getInstance();
	cacher->addSpriteFramesWithFile("survivor/meleeattack_flashlight.plist");

	Gambler* someSprite = new Gambler("survivor");
	/*someSprite->initWithSpriteFrameName("survivor-meleeattack_handgun_0.png");
	someSprite->setAnchorPoint(Vec2(0,0));
	
	//someSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(someSprite, 3);

	// load all the animation frames into an array
	const int kNumberOfFrames = 15;
	Vector<SpriteFrame*> frames;

	for (int i = 0; i < kNumberOfFrames; i++)
	{
		std::string ss;
		ss = "survivor-meleeattack_handgun_" + std::to_string(i) + ".png";
		frames.pushBack(cacher->getSpriteFrameByName(ss));
	}

	// play the animation
	Animation* anim = new Animation;
	anim->initWithSpriteFrames(frames, 0.05f);
	auto animation = Animate::create(anim);
	
	auto scale = ScaleBy::create(0.0001, 0.4);
	auto scaleRev = scale->reverse();
	
	auto moveby = MoveBy::create(0.5, Vec2(0, 300));
	auto moveBack = moveby->reverse();
	auto bounce = EaseBounceOut::create(moveBack);

	auto delay = DelayTime::create(1);

	someSprite->runAction(scale);
	someSprite->runRight();
//	auto animSeq = Sequence::create(scale, animation, animation, animation, scaleRev, moveby, nullptr);
//	auto animSeq = Sequence::create(moveby, bounce, delay, nullptr);
//	someSprite->runAction(RepeatForever::create(animSeq));

	//someSprite->runAction(moveby);
	*/

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
