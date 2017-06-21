#include "cocos2d.h"
#include "Constants.h"
USING_NS_CC;

class LevelMap : public TMXTiledMap {
public:
	LevelMap();
	LevelMap(const std::string& tmxFile, Layer* layer);
	
	void initFirstLevel();
	static void initWithPhysicsBox(Sprite* sprite, Size size, PhysicsMaterial material, Vec2 offset, bool isDynamic, int contactBitmask);

	void setMap(const std::string& tmxFile, Layer* layer=nullptr);
	TMXTiledMap* getMap();

protected:
	Layer* _layer;

private:
	TMXTiledMap* _map;
};