#include "Brick.h"

//constructor gets an int to 
//initialize the brick size
Brick::Brick(int brickNum) {
	//loading the brick texture files
	brickTexture.loadFromFile("../Matrix_Hüner_OOP_Project/assets/brick.png");
	brickTexture.setRepeated(true);
	sprite.setTexture(brickTexture);
	float brickWidth = sprite.getTextureRect().width;
	float brickHeight = sprite.getTextureRect().height;
	sprite.setOrigin(0, 0);
	sprite.setTextureRect(IntRect(0, 0, (brickNum * brickWidth), brickHeight));
};


