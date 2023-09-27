#include "SPipeFlipped.h"

//loading the texture file
FlippedSPipe::FlippedSPipe() {
	flippedSPipeTexture.loadFromFile("../Matrix_Hüner_OOP_Project/assets/pipeS.png");
	sprite.setTexture(flippedSPipeTexture);
	//flipping the sprite
	sprite.setScale(-1.0f, 1.0f);
};

