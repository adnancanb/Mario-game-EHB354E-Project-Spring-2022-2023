#include "Scoreboard.h"

//initializing the lives and scores to
//the initial game conditions
//and loading the texture files
ScoreBoard::ScoreBoard() //constructor
{
	this->lives = 3;
	this->score = 0;
	texture.loadFromFile("../Matrix_Hüner_OOP_Project/assets/mariohead.png");
	sprite.setTexture(texture);
	font.loadFromFile("../Matrix_Hüner_OOP_Project/assets/font.ttf");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setColor(Color::White);
	text.setStyle(Text::Bold);
}

//printing the lives into the screen
void ScoreBoard::printLives(RenderWindow& window)
{
	for (int i = 0; i < this->lives; i++)
	{
		sprite.setPosition(Vector2f(float(90.0f + 40*i), float(90.0f)));
		window.draw(sprite);
	}
}

//printing the score into the screen
void ScoreBoard::printScore(RenderWindow& window)
{
	stringstream ss;
	ss << this->score;
	string scr;
	ss >> scr;
	text.setString(scr);
	text.setPosition(Vector2f(float(90), float(50)));
	window.draw(text);
}

//setting the score
void ScoreBoard::setScore(int score)
{
	this->score = score;
}
//getting the score
int ScoreBoard::getScore()
{
	return this->score;
}
//setting the lives
void ScoreBoard::setLives(int lives)
{
	this->lives = lives;
}
//getting the lives
int ScoreBoard::getLives()
{
	return this->lives;
}