#pragma once
#include "Common.h"
#include "Object.h"

class Brick :public Object {
	Texture brickTexture;
public:
	Brick(int);
};