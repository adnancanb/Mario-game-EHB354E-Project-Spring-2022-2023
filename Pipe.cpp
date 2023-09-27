#include "Pipe.h"

//loading the texture file
Pipe::Pipe() {
	pipeTexture.loadFromFile("../Matrix_Hüner_OOP_Project/assets/pipe.png");
	sprite.setTexture(pipeTexture);
};

