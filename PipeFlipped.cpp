#include "PipeFlipped.h"

//loading the texture file
FlippedPipe::FlippedPipe() {
	flippedPipeTexture.loadFromFile("../Matrix_Hüner_OOP_Project/assets/pipe.png");
	sprite.setTexture(flippedPipeTexture);
	//setting the rotation to flip the pipe image
	sprite.setRotation(180.0f);
};
