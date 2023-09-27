#include "Floor.h"



Floor::Floor() {
	//loading the floor texture file
	floorTexture.loadFromFile("../Matrix_Hüner_OOP_Project/assets/floor.png");
	floorTexture.setRepeated(true);
	sprite.setTexture(floorTexture);
	int floorWidth = sprite.getTextureRect().width;
	int floorHeight = sprite.getTextureRect().height;
	sprite.setTextureRect(IntRect(0, 0, WINDOW_WIDTH, floorHeight));

};



