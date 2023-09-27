#include "menu.h"

Menu::Menu()
{
	//load the fonts, texts, and textures
	window = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");
	font.loadFromFile("../Matrix_Hüner_OOP_Project/assets/font.ttf");
	text[0].setFont(font);
	text[0].setCharacterSize(75);
	text[0].setColor(Color::Magenta);
	text[0].setStyle(Text::Bold);

	text[1].setFont(font);
	text[1].setCharacterSize(40);
	text[1].setColor(Color::Red);
	text[1].setStyle(Text::Bold);

	text[2].setFont(font);
	text[2].setCharacterSize(30);
	text[2].setColor(Color::Green);
	text[2].setStyle(Text::Italic);

	brickone.loadFromFile("../Matrix_Hüner_OOP_Project/assets/brick.png");
	brickone.setRepeated(true);
	brickonesprite.setTexture(brickone);
	float brickWidth = brickonesprite.getTextureRect().width;
	float brickHeight = brickonesprite.getTextureRect().height;
	brickonesprite.setTextureRect(IntRect(0, 0, (WINDOW_WIDTH * 0.75f), (brickHeight)));

	floor.loadFromFile("../Matrix_Hüner_OOP_Project/assets/floor.png");
	floor.setRepeated(true);
	floorsprite.setTexture(floor);
	int floorWidth = floorsprite.getTextureRect().width;
	int floorHeight = floorsprite.getTextureRect().height;
	floorsprite.setTextureRect(IntRect(0, 0, WINDOW_WIDTH, floorHeight));

	pipe.loadFromFile("../Matrix_Hüner_OOP_Project/assets/pipe.png");
	pipesprite.setTexture(pipe);
	pipesprite.setScale(1.0f, 1.0f);

	flippedpipe.loadFromFile("../Matrix_Hüner_OOP_Project/assets/pipe.png");
	flippedpipesprite.setTexture(flippedpipe);
	flippedpipesprite.setRotation(180.0f);

	mariohead.loadFromFile("../Matrix_Hüner_OOP_Project/assets/mariohead.png");
	marioheadsprite.setTexture(mariohead);

	marioheadflipped.loadFromFile("../Matrix_Hüner_OOP_Project/assets/mariohead.png");
	marioheadflippedsprite.setTexture(marioheadflipped);
	marioheadflippedsprite.setScale(-1.0f, 1.0f);

	mario.loadFromFile("../Matrix_Hüner_OOP_Project/assets/mario1.png");
	mariosprite.setTexture(mario);

	turtle.loadFromFile("../Matrix_Hüner_OOP_Project/assets/turtle2.png");
	turtlesprite.setTexture(turtle);
}

int Menu::MainMenu()
{


	while (window->isOpen())
	{
		Event event;

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window->close();
				return 2;
			}
			if (event.key.code == Keyboard::Enter)
			{
				window->close();
				return 1;
			}
		}
		
		window->clear();

		//drawing the main menu graphics
		text[0].setString("MARIO");
		text[0].setPosition(Vector2f(float((WINDOW_WIDTH / 2) - 135), float((WINDOW_HEIGHT / 2) - 250)));
		window->draw(text[0]);

		text[1].setString("PRESS 'ENTER' TO START A NEW GAME ");
		text[1].setPosition(Vector2f(float((WINDOW_WIDTH / 2) - 450), float((WINDOW_HEIGHT / 2) + 100)));
		window->draw(text[1]);

		brickonesprite.setPosition(120.0f, 100.0f);
		window->draw(brickonesprite);

		brickonesprite.setPosition(120.0f, 350.0f);
		window->draw(brickonesprite);

		floorsprite.setPosition(Vector2f(0.0f, float(WINDOW_HEIGHT - (floorsprite.getTextureRect().height))));
		window->draw(floorsprite);

		pipesprite.setPosition(Vector2f(WINDOW_WIDTH - (pipesprite.getTextureRect().width), float(WINDOW_HEIGHT - (floorsprite.getTextureRect().height) - (pipesprite.getTextureRect().height))));
		window->draw(pipesprite);
		
		flippedpipesprite.setPosition(Vector2f(float(flippedpipesprite.getTextureRect().width), float(WINDOW_HEIGHT - (floorsprite.getTextureRect().height))));
		window->draw(flippedpipesprite);
		
		marioheadsprite.setPosition(Vector2f(float((WINDOW_WIDTH / 2) + 147.5f), float((WINDOW_HEIGHT / 2) - 207.5f)));
		window->draw(marioheadsprite);
		
		marioheadflippedsprite.setPosition(Vector2f(float((WINDOW_WIDTH / 2) - 148.5f), float((WINDOW_HEIGHT / 2) - 207.5f)));
		window->draw(marioheadflippedsprite);
		
		mariosprite.setPosition(Vector2f(float(840.0f - mariosprite.getTextureRect().width), float(350.0f - mariosprite.getTextureRect().height)));
		window->draw(mariosprite);
		
		turtlesprite.setPosition(Vector2f(float(120.0f), float(350.0f - turtlesprite.getTextureRect().height)));
		window->draw(turtlesprite);

		text[2].setString("MATRIX HUNER PRODUCTION");
		text[2].setPosition(Vector2f(float((WINDOW_WIDTH / 2) - 245), float(WINDOW_HEIGHT - 2 * (floorsprite.getTextureRect().height))));
		window->draw(text[2]);


		window->display();
	}
}
