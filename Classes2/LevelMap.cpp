#include "LevelMap.h"

void LevelMap::initWithPhysicsBox(Sprite* sprite, Size size, PhysicsMaterial material, Vec2 offset=Vec2::ZERO, bool isDynamic=true, int contactBitmask=0xFFFFFFFF) {
	PhysicsBody* physicsBody = PhysicsBody::createBox(size, material, offset);
	physicsBody->setDynamic(isDynamic);
	physicsBody->setContactTestBitmask(contactBitmask);
	if (sprite)
		sprite->addComponent(physicsBody);
}

LevelMap::LevelMap():
	_map(nullptr)
{
}

LevelMap::LevelMap(const std::string& tmxFile, Layer* layer) {
	_map = TMXTiledMap::create(tmxFile);
	_layer = layer;
}

void LevelMap::setMap(const std::string& tmxFile, Layer* layer) {
	_map = TMXTiledMap::create(tmxFile);
	if (layer)
		layer->addChild(_map);
}

TMXTiledMap* LevelMap::getMap() {
	return _map;
}

void LevelMap::initFirstLevel() {
	auto mapSize = _map->getContentSize();
	auto tileSize = _map->getTileSize();

	/**** Layers ****/
	auto meta = _map->getLayer("Meta");
	meta->setVisible(false);
	auto boxes = _map->getLayer("boxes");
	auto ground = _map->getLayer("ground");
	auto collect = _map->getLayer("collectable");
	/****************/

	auto groundSize = ground->getLayerSize();
	auto boxesSize = boxes->getLayerSize();

	for (int i = 0; i < boxesSize.width; ++i) {
		for (int j = 0; j < boxesSize.height; ++j) {
			auto sprite = boxes->getTileAt(Vec2(i, j));
			if (sprite) {
				sprite->setTag(BOX_TAG);
				initWithPhysicsBox(sprite, tileSize, PhysicsMaterial(0.5f, 0.0f, 0.5f));
			}
		}
	}

	/* Creating the bounding of map */
	/* Left */
	auto sprite = Sprite::create(); sprite->setPosition(Vec2(-tileSize.width / 2, tileSize.height * (groundSize.height - 0.5))); _layer->addChild(sprite);
	initWithPhysicsBox(sprite, Size(tileSize.width, tileSize.height * groundSize.height), PhysicsMaterial(1.0f, 1.0f, 0.0f), Vec2(0, -tileSize.height * (groundSize.height - 1) / 2), false);
	/* Up */
	sprite = Sprite::create(); sprite->setPosition(Vec2(tileSize.width / 2, tileSize.height * (groundSize.height + 0.5))); _layer->addChild(sprite);
	initWithPhysicsBox(sprite, Size(tileSize.width * groundSize.width, tileSize.height), PhysicsMaterial(1.0f, 1.0f, 0.0f), Vec2(tileSize.width * (groundSize.width - 1) / 2, 0), false);
	/* Right */
	sprite = Sprite::create(); sprite->setPosition(Vec2(tileSize.width * (groundSize.width + 0.5), tileSize.height * (groundSize.height - 0.5))); _layer->addChild(sprite);
	initWithPhysicsBox(sprite, Size(tileSize.width, tileSize.height * groundSize.height), PhysicsMaterial(1.0f, 1.0f, 0.0f), Vec2(0, -tileSize.height * (groundSize.height - 1) / 2), false);
	/* Down */
	sprite = Sprite::create(); sprite->setPosition(Vec2(tileSize.width / 2, -tileSize.height / 2)); _layer->addChild(sprite);
	initWithPhysicsBox(sprite, Size(tileSize.width * groundSize.width, tileSize.height), PhysicsMaterial(1.0f, 1.0f, 0.0f), Vec2(tileSize.width * (groundSize.width - 1) / 2, 0), false);


	auto objects = _map->getObjectGroup("fixtures");

	/* Physics for lakes */
	for (int i = 1; true; ++i) {
		Value val = Value(i);
		auto lake = objects->getObject("lake" + val.asString());
		if (lake.empty())
			break;
		auto pointsVal = lake["points"];
		auto pointsVector = pointsVal.asValueVector();
		Point* points = new Point[pointsVector.size()];
		for (int j = 0; j < pointsVector.size(); ++j) {
			points[j].x = pointsVector[j].asValueMap()["x"].asFloat();
			points[j].y = -pointsVector[j].asValueMap()["y"].asFloat();
		}
		auto sprite = Sprite::create();
		sprite->setPosition(lake["x"].asFloat(), lake["y"].asFloat());

		auto physicsBody = PhysicsBody::createPolygon(points, pointsVector.size());
		physicsBody->setDynamic(false);
		physicsBody->setContactTestBitmask(0xFFFFFFFF);
		sprite->addComponent(physicsBody);
		sprite->setTag(LAKE_TAG);
		_layer->addChild(sprite);
	}
}