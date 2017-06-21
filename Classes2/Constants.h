#pragma once
#define SURVIVOR_SCALE		0.3f
#define BULLET_SCALE		0.2f

#define PLAYER_TAG			1
#define BULLET_TAG			2
#define BOUND_TAG			3

#define FLASH_IDLE			"-idle_flashlight"
#define FLASH_MELEE			"-meleeattack_flashlight"
#define FLASH_MOVE			"-move_flashlight"

#define KNIFE_IDLE			"-idle_knife"
#define KNIFE_MELEE			"-meleeattack_knife"
#define KNIFE_MOVE			"-move_knife"

#define HANDGUN_IDLE		"-idle_handgun"
#define HANDGUN_MELEE		"-meleeattack_handgun"
#define HANDGUN_MOVE		"-move_handgun"
#define HANDGUN_RELOAD		"-reload_handgun"
#define HANDGUN_SHOOT		"-shoot_handgun"

#define RIFLE_IDLE			"-idle_rifle"
#define RIFLE_MELEE			"-meleeattack_rifle"
#define RIFLE_MOVE			"-move_rifle"
#define RIFLE_RELOAD		"-reload_rifle"
#define RIFLE_SHOOT			"-shoot_rifle"

#define SHOTGUN_IDLE		"-idle_shotgun"
#define SHOTGUN_MELEE		"-meleeattack_shotgun"
#define SHOTGUN_MOVE		"-move_shotgun"
#define SHOTGUN_RELOAD		"-reload_shotgun"
#define SHOTGUN_SHOOT		"-shoot_shotgun"

#define DEF_PLAYER_VELOCITY		120.0f
#define DEF_PLAYER_DIAG_VELOCITY	DEF_PLAYER_VELOCITY/sqrt(2)

#define DEF_BULLET_VELOCITY		500.0f

#define UP_ANGLE			-90.0f
#define RIGHT_UP_ANGLE		-45.0f
#define RIGHT_ANGLE			0.0f
#define RIGHT_DOWN_ANGLE	45.0f
#define DOWN_ANGLE			90.0f
#define LEFT_DOWN_ANGLE		135.0f
#define LEFT_ANGLE			180.0f
#define LEFT_UP_ANGLE		-135.0f

#define ROTATE_DURATION		0.1f
#define ANIM_DELAY			0.05f

enum class Direction {
	UP,
	UP_RIGHT,
	RIGHT_UP = UP_RIGHT,
	RIGHT,
	RIGHT_DOWN,
	DOWN_RIGHT = RIGHT_DOWN,
	DOWN,
	DOWN_LEFT,
	LEFT_DOWN = DOWN_LEFT,
	LEFT,
	LEFT_UP,
	UP_LEFT = LEFT_UP
};