#pragma once
#include "Common.h"

class Menu
{
	RenderWindow* window;
	Font font;
	Text text[3];

	Texture brickone;
	Sprite brickonesprite;

	Texture floor;
	Sprite floorsprite;

	Texture pipe;
	Sprite pipesprite;

	Texture flippedpipe;
	Sprite flippedpipesprite;

	Texture mariohead;
	Sprite marioheadsprite;

	Texture marioheadflipped;
	Sprite marioheadflippedsprite;

	Texture mario;
	Sprite mariosprite;

	Texture turtle;
	Sprite turtlesprite;

public:
	Menu();
	int MainMenu(void);
};