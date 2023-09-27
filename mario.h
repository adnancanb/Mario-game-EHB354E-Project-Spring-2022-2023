#pragma once
#include "Common.h"
#include "Object.h"



class Mario :public Object {
	Texture marioTexture;
	Texture marioTextureMovementEffect[3];
	Clock clock;
	float marioWidth;
	float marioHeight;
	int currentTextureIndex;
	bool death_marker;

public:
	Mario();
	void move();
	void mario_jump(bool onAir);
	void decrease_X_velocity(void);
	void set_Y_velocity(float);
	void set_X_velocity(float);
	float get_Y_velocity(void);
	void fall(void);
	void respawn(bool);
	bool get_marker(void);
};

