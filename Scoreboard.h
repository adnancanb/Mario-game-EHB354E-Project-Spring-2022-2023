#pragma once
#include "Common.h"

class ScoreBoard 
{
	int score;
	int lives;
	Texture texture;
	Sprite sprite;
	Font font;
	Text text;
public:
	ScoreBoard();
	void setScore(int score);
	int getScore(void);
	void setLives(int lives);
	int getLives(void);
	void printScore(RenderWindow&);
	void printLives(RenderWindow&);
};
