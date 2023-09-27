#include "SPipe.h"

//loading the texture file
SPipe::SPipe() {
	sPipeTexture.loadFromFile("../Matrix_Hüner_OOP_Project/assets/pipeS.png");
	sprite.setTexture(sPipeTexture);
};

