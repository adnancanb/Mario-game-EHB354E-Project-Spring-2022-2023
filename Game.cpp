#include "Game.h"
using namespace std;

Game::Game(int speed) //constructor for Game Class
{
	//initializing the attributes
	this->speed = speed;
	clock.restart();
	this->listSize = 0;
	this->deathTurtleSize = 0;

	scoreboard = new ScoreBoard();

	window = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");


	//SETTING POSITIONS OF FLOOR
	floor = new Floor;
	floor->setPosition(Vector2f(0.0f, float(WINDOW_HEIGHT - (floor->findHeight()))));

	//SETTING POSITIONS OF BRICKS
	brick_vec[0] = new Brick(12);
	brick_vec[0]->setPosition(Vector2f(0.0f, FIRST_BRICK_HEIGHT));

	brick_vec[1] = new Brick(12);
	brick_vec[1]->setPosition(Vector2f(float(WINDOW_WIDTH - brick_vec[1]->findWidth()), FIRST_BRICK_HEIGHT));

	brick_vec[2] = new Brick(16);
	brick_vec[2]->setPosition(Vector2f(float((WINDOW_WIDTH / 2.0f) - (brick_vec[2]->findWidth()) / 2.0f), float(FIRST_BRICK_HEIGHT + 5.0f * brick_vec[2]->findHeight())));

	brick_vec[3] = new Brick(4);
	brick_vec[3]->setPosition(Vector2f(0.0f, float(FIRST_BRICK_HEIGHT + 6.2f * brick_vec[3]->findHeight())));

	brick_vec[4] = new Brick(4);
	brick_vec[4]->setPosition(Vector2f(float(WINDOW_WIDTH - brick_vec[4]->findWidth()), float(FIRST_BRICK_HEIGHT + 6.2f * brick_vec[4]->findHeight())));

	brick_vec[5] = new Brick(12);
	brick_vec[5]->setPosition(Vector2f(0.0f, float(FIRST_BRICK_HEIGHT + 10.5f * brick_vec[5]->findHeight())));

	brick_vec[6] = new Brick(12);
	brick_vec[6]->setPosition(Vector2f(float(WINDOW_WIDTH - brick_vec[6]->findWidth()), float(FIRST_BRICK_HEIGHT + 10.5f * brick_vec[6]->findHeight())));

	//SETTING POSITIONS OF PIPES
	pipe = new Pipe;
	pipe->setPosition(Vector2f(float(WINDOW_WIDTH - (pipe->findWidth())), float(WINDOW_HEIGHT - (floor->getGlobalBounds().height) - (pipe->findHeight()))));

	flippedPipe = new FlippedPipe;
	flippedPipe->setPosition(Vector2f(float(pipe->findWidth()), float(WINDOW_HEIGHT - (floor->getGlobalBounds().height))));

	sPipe = new SPipe();
	sPipe->setPosition(Vector2f(0.0f, float(FIRST_BRICK_HEIGHT - (brick_vec[0]->findHeight()) - (sPipe->findHeight()))));
	 
	flippedSPipe = new FlippedSPipe();
	flippedSPipe->setPosition(Vector2f(float(WINDOW_WIDTH), float(FIRST_BRICK_HEIGHT - (brick_vec[0]->findHeight()) - (sPipe->findHeight()))));

	//initialize the game with 1 mario and 1 turtle
	addMario();
	addTurtle();

	//specify the starting aggravation ratio for turtles
	this->aggrevateRatio = 1;

	//initializing the clock for aggravation
	aggrevation.restart();
}

Mario* Game::addMario()//mario will be the last element of the list
{
	//adding the Mario to the list
	this->listSize++;
	Mario* mario = new Mario();
	mario->next = object;
	object = mario;
	return mario;
}

Object* Game::getMario()
{
	//getting the mario from the list
	//mario will be the last element of the list (stack)
	Object* mario = object;
	while (mario->next != NULL)
	{
		mario = mario->next;
	}
	return mario;
}

Turtle* Game::addTurtle()
{
	//adding a turtle to the list
	this->listSize++;
	Turtle* turtle = new Turtle();
	turtle->next = object;
	object = turtle;
	return turtle;
}

void Game::deleteTurtle(Object* turtle)
{
	//deleting the specified turtle from list
	this->listSize = this->listSize - 1;
	Object* curr = object;
	Object* prev = NULL;
	while (curr)
	{
		if (curr == turtle)
		{
			if (prev)
			{
				prev->next = curr->next;
			}
			else
			{
				object = curr->next;
			}
			delete curr;
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

Object* Game::getTurtle(int index)
{
	//gettin the turtle from the list
	//int index corresponds to the
	//index'th turtle
	Object* temp = object;
	for (int i = 0; i < index; i++)
	{
		temp = temp->next;
	}
	return temp;
}

int Game::getTurtleSize()
{
	//returns the turtle size
	return (this->listSize-1);
}

int Game::check_pipe_collision(Object* object) 
{
	//checking the objects location and the 
	//pipes location to see if there exists a collision
	//in between
	if (object->boundingBox().width + object->getPosition().x + 60.0f >= pipe->getPosition().x + pipe->findWidth()
		&& object->getPosition().y >= 700.0f)
	{
		return 1;
	}
	else if (object->boundingBox().width + object->getPosition().x + 40.0f <= flippedPipe->getPosition().x + flippedPipe->getGlobalBounds().width
			 && object->getPosition().y >= 700.0f)
	{
		return 2;
	}
	else {
		return 0;
	}
	
}

void Game::drawBackground(RenderWindow& window)
{	
	//drawing all the background sprites
	//to the screen
	for (int i = 0; i < 7; i++)
	{
		brick_vec[i]->draw(window);
	}

	floor->draw(window);
	pipe->draw(window);
	flippedPipe->draw(window);
	sPipe->draw(window);
	flippedSPipe->draw(window);
	scoreboard->printLives(window);
	scoreboard->printScore(window);
}


bool Game::onFloor(Object *object)
{
	//checking if the object is on floor
	//or on a brick
	//returns true if it is on any surface
	if (object->boundingBox().height / 2.0f + object->getPosition().y + 30.0f >= floor->getPosition().y + floor->getGlobalBounds().height / 2.0f)
	{
		return true;
	}
	else
	{
		for (int i = 0; i < 7; i++)
		{
			if (object->getPosition().y + object->getGlobalBounds().height / 2.0f >= brick_vec[i]->getPosition().y
				&& object->getPosition().y + object->getGlobalBounds().height / 2.0f <= brick_vec[i]->getPosition().y + brick_vec[i]->getGlobalBounds().height / 2.0f
				&& object->getPosition().x + object->getGlobalBounds().width >= brick_vec[i]->getPosition().x + 30.0f
				&& object->getPosition().x - 20.0f <= brick_vec[i]->getPosition().x + brick_vec[i]->getGlobalBounds().width)
			{
				return true;
			}
		}
	}
	return false;

}


bool Game::mario_onFloor(Object *object)
{
	//check mario if its on Floor
	//its implemented seperately for mario
	//since the origins are not at the same location
	//as turtle
	//which will lead to different tolerances
	if (object->boundingBox().height / 2.0f + object->getPosition().y - 10.0f >= floor->getPosition().y + floor->getGlobalBounds().height / 2.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Game::mario_onBrick(Object* object)
{
	//checks whether mario stands on a brick
	//if it is standing on a brick it returns true
	//it helps mario to stand on bricks without passing through them
	for (int i = 0; i < 7; i++)
	{
		float brick_position_left = brick_vec[i]->getPosition().x;
		float brick_position_right = brick_vec[i]->getPosition().x + (brick_vec[i]->getGlobalBounds().width);
		float brick_surface = brick_vec[i]->getPosition().y + brick_vec[1]->getGlobalBounds().height;
		float mario_half = object->getGlobalBounds().width / 2.0f;
		float tolerance = 10.0f;
		float horizontal_tolerance = 5.0f; 
		if ((object->getPosition().y + brick_vec[i]->getGlobalBounds().height >= brick_surface - (tolerance / 2.0f)) 
			&& (object->getPosition().y + brick_vec[i]->getGlobalBounds().height <= brick_surface + (tolerance / 1.0f)) 
			&& (object->getPosition().x >= brick_position_left - mario_half) 
			&& (object->getPosition().x <= brick_position_right + mario_half))
		{
			return true;
		}
	}
	return false;
}

bool Game::mario_hitBottomBrick(Object* object)
{
	//checks whether mario hits the brick from under the brick or not
	//return true if it does
	//it prevents mario to pass through bricks from below
	for (int i = 0; i < 7; i++)
	{
		float brick_position_left = brick_vec[i]->getPosition().x;
		float brick_position_right = brick_vec[i]->getPosition().x + (brick_vec[i]->getGlobalBounds().width);
		float brick_bottom = brick_vec[i]->getPosition().y + brick_vec[i]->getGlobalBounds().height;
		float mario_half = object->getGlobalBounds().width / 2.0f;
		float mario_top = object->getPosition().y - object->getGlobalBounds().height;
		float tolerance = 7.5f;
		if ((mario_top <= brick_bottom + tolerance)
			&& (mario_top >= brick_bottom - tolerance)
			&& (object->getPosition().x >= brick_position_left - mario_half)
			&& (object->getPosition().x <= brick_position_right + mario_half))
		{
			return true;
		}
	}
	return false;
}

bool Game::mario_checkBrickSides(Object* object)
{
	//checks whether mario hits the brick from edges of the brick or not
	//return true if it does
	//it prevents mario to pass through bricks from edges
	for (int i = 0; i < 7; i++)
	{
		float brick_position_left = brick_vec[i]->getPosition().x;
		float brick_position_right = brick_vec[i]->getPosition().x + brick_vec[i]->getGlobalBounds().width;
		float higher_edge = brick_vec[i]->getPosition().y;
		float lower_edge = brick_vec[i]->getPosition().y + brick_vec[i]->getGlobalBounds().height;
		float mario_left = object->getPosition().x - (object->getGlobalBounds().width / 2.0f);
		float mario_right = object->getPosition().x + (object->getGlobalBounds().width / 2.0f);
		float mario_top = object->getPosition().y - object->getGlobalBounds().height;
		float mario_bot = object->getPosition().y;
		float tolerance = 10.0f;

		if ((mario_bot >= higher_edge + tolerance)
			&& (mario_top <= lower_edge - tolerance)
			&& (mario_left <= brick_position_right + (tolerance/2.0f))
			&& (mario_right >= brick_position_left - (tolerance/2.0f)))
		{
			return true;
		}
	}
	return false;
}

//FOLLOWING MARIO_HITPIPE FUNCTIONS ALL DO THE SAME THING
//THESE FUNCTIONS PREVENT MARIO TO PASS THROUGH ANY PIPE IN THE SCREEN
//SAME LOGIC IS ALSO APPLIED FOR THE METHODS FOR TURTLE BELOW 
bool Game::mario_hitPipe(Object* object) //bottom right pipe
{
	float pipes_top = pipe->getPosition().y;
	float pipes_bot = pipe->getPosition().y + pipe->getGlobalBounds().height;
	float pipe_right = pipe->getPosition().x + pipe->getGlobalBounds().width;
	float pipe_left = pipe->getPosition().x; 
	float mario_left = object->getPosition().x - (object->getGlobalBounds().width / 2.0f);
	float mario_right = object->getPosition().x + (object->getGlobalBounds().width / 2.0f);
	float mario_top = object->getPosition().y - object->getGlobalBounds().height;
	float mario_bot = object->getPosition().y;
	float tolerance = 5.0f;
	if ((mario_top >= brick_vec[6]->getPosition().y + brick_vec[6]->getGlobalBounds().height - tolerance)
		&& (mario_right >= pipe_left - tolerance)
		&& (mario_right <= pipe_left + tolerance))
	{
		return true;
	}
	return false;
}

bool Game::mario_hitPipe_Flipped(Object* object) //bottom left pipe
{
	float pipes_top = pipe->getPosition().y;
	float pipes_bot = pipe->getPosition().y + pipe->getGlobalBounds().height;
	float flipped_pipe_right = flippedPipe->getPosition().x;
	float flipped_pipe_left = flippedPipe->getPosition().x - flippedPipe->getGlobalBounds().width; 
	float mario_left = object->getPosition().x - (object->getGlobalBounds().width / 2.0f);
	float mario_right = object->getPosition().x + (object->getGlobalBounds().width / 2.0f);
	float mario_top = object->getPosition().y - object->getGlobalBounds().height;
	float mario_bot = object->getPosition().y;
	float tolerance = 5.0f;

	if ((mario_top >= brick_vec[6]->getPosition().y + brick_vec[6]->getGlobalBounds().height - tolerance) 
		&& (mario_left >= flipped_pipe_right - tolerance)
		&& (mario_left <= flipped_pipe_right + tolerance))
	{
		return true;
	}
	return false;
}

bool Game::mario_hit_S_Pipe(Object* object) //top left pipe
{
	float s_pipes_top = sPipe->getPosition().y;
	float s_pipes_bot = sPipe->getPosition().y + sPipe->getGlobalBounds().height;
	float s_pipe_right = sPipe->getPosition().x + sPipe->getGlobalBounds().width;
	float s_pipe_left = sPipe->getPosition().x;
	float mario_left = object->getPosition().x - (object->getGlobalBounds().width / 2.0f);
	float mario_right = object->getPosition().x + (object->getGlobalBounds().width / 2.0f);
	float mario_top = object->getPosition().y - object->getGlobalBounds().height;
	float mario_bot = object->getPosition().y;
	float tolerance = 5.0f;
	if ((mario_bot <= brick_vec[0]->getPosition().y + tolerance)
			&& (mario_left <= s_pipe_right + tolerance)
			&& (mario_left >= s_pipe_right - tolerance) )
	{
		return true;
	}
	return false;
}

bool Game::mario_hit_S_Pipe_Flipped(Object* object) //top right pipe
{
	float s_pipes_top = sPipe->getPosition().y;
	float s_pipes_bot = sPipe->getPosition().y + sPipe->getGlobalBounds().height;
	float s_flipped_pipe_right = flippedSPipe->getPosition().x;
	float s_flipped_pipe_left = flippedSPipe->getPosition().x - flippedSPipe->getGlobalBounds().width;
	float mario_left = object->getPosition().x - (object->getGlobalBounds().width / 2.0f);
	float mario_right = object->getPosition().x + (object->getGlobalBounds().width / 2.0f);
	float mario_top = object->getPosition().y - object->getGlobalBounds().height;
	float mario_bot = object->getPosition().y;
	float tolerance = 5.0f;
	if ((mario_bot <= brick_vec[0]->getPosition().y + tolerance)
		&& (mario_right >= s_flipped_pipe_left - tolerance)
		&& (mario_right <= s_flipped_pipe_left + tolerance) )
	{
		return true;
	}
	return false;
}

//FOR TURTLE
bool Game::turtle_hit_S_Pipe(Object* object)
{
	float turtle_y = object->getPosition().y;
	float s_pipe_right = sPipe->getPosition().x + sPipe->getGlobalBounds().width;
	float turtle_left = object->getPosition().x - (object->getGlobalBounds().width / 2.0f);
	float tolerance = 10.0f;

	if ((turtle_y < brick_vec[0]->getPosition().y)
		&& (turtle_left < s_pipe_right - tolerance))
	{
		return true;
	}

	return false;
}

bool Game::turtle_hit_S_Pipe_Flipped(Object* object)
{
	float turtle_y = object->getPosition().y;
	float s_flipped_pipe_left = flippedSPipe->getPosition().x - flippedSPipe->getGlobalBounds().width;
	float turtle_right = object->getPosition().x + (object->getGlobalBounds().width / 2.0f);
	float tolerance = 10.0f;
	if ((turtle_y < brick_vec[0]->getPosition().y)
		&& (turtle_right > s_flipped_pipe_left + tolerance))
	{
		return true;
	}
	return false;
}

//to check if the turtle is 
//out of bounds
//this methods is used to make turtle stay in the map
int Game::checksides(Object* object) //for turtle
{
	if (object->boundingBox().width + object->getPosition().x >= WINDOW_WIDTH + 25)
	{
		return 1;
	}
	else if (object->boundingBox().width + object->getPosition().x <= 85)
	{
		return 2;
	}
	return 0;
}

//checks if there exsits a collision between two objects
bool Game::checkCollusion(Object* mario_object, Object* turtle_object)
{
	if (mario_object->getGlobalBounds().intersects(turtle_object->getGlobalBounds()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game::endGameDisplay(bool check, RenderWindow& window)
{
	//gets bool check for checking the the player won or lost
	//and printing the end game display accordingly
	font.loadFromFile("../Matrix_Hüner_OOP_Project/assets/font.ttf");
	text.setFont(font);
	text.setCharacterSize(70);
	text.setColor(Color::Red);
	text.setStyle(Text::Bold);
	if (check) //YOU WIN SCREEN
	{
		text.setString("YOU WIN!");
		text.setPosition(Vector2f(float((WINDOW_WIDTH / 2) - 160), float((WINDOW_HEIGHT / 2) - 100)));
	}
	else //GAME OVER SCREEN
	{
		text.setString("GAME OVER!");
		text.setPosition(Vector2f(float((WINDOW_WIDTH / 2) - 240), float((WINDOW_HEIGHT / 2) - 100)));
	}
	window.draw(text);
}

int Game::update(void)
{
	//end game condition 
	//initialized as false since the game has not ended
	bool endGame = false; 
	//bool array for each turtle
	//for checking if a turtle has collided
	//with another turtle
	bool collision[5] = { true, true, true, true, true };

	while (window->isOpen()) {

		Event event;

		while (window->pollEvent(event)) {
			if (event.type == Event::Closed) {
				window->close();
				return 2;
			}
		}

		window->clear(sf::Color::Black);
		drawBackground(*window);

		//drawing the mario
		getMario()->draw(*window);

		//drawing turtle
		for (int i = 0; i < getTurtleSize(); i++)
		{
			getTurtle(i)->draw(*window);
		}


		//end game conditions
		if (scoreboard->getLives() == 0)
		{
			this->listSize = 0; //clear the turtle from the screen
			endGameDisplay(false, *window);
			endGame = true;
		}
		else if (scoreboard->getScore() == 500)
		{
			this->listSize = 0; //clear the turtle from the screen
			endGameDisplay(true, *window);
			endGame = true;
		}

		window->display();

		//if the game ends, sleep for 5 seconds and return to main menu
		if (endGame)
		{
			sf::sleep((seconds(3)));
			window->close();
			return 0;
		}


		//aggrevate all turtles every 20 seconds
		if (aggrevation.getElapsedTime().asSeconds() > 20)
		{
			//aggravation ratio cannot exists 2.5
			//since after that the game becomes
			//extremely fast
			if (this->aggrevateRatio < 2.50f)
			{
				this->aggrevateRatio *= 1.1f;
				aggrevation.restart();
			}
		}

		//turtle loop to do turtle things 
		for (int i = 0; i < getTurtleSize(); i++)
		{
			if (!getTurtle(i)->get_marker()) //checking if the turtle is alive or not
			{

				Vector2f turtle_pos = getTurtle(i)->getPosition();
				getTurtle(i)->setPosition(turtle_pos);

				//updating the turtles Vy velocity
				getTurtle(i)->velocity_Y_update();

				//state diagram for animations
				getTurtle(i)->state_diagram();

				//checking if the turtle is on Floor
				if (onFloor(getTurtle(i)))
				{
					getTurtle(i)->setDown(false);
				}
				else {
					getTurtle(i)->setDown(true);
				}

				getTurtle(i)->jump();


				//checks if the turtle is out of bounds
				if (checksides(getTurtle(i)))
				{
					//prevents the turtle from going
					//out of bounds and changes its heading accordingly
					if (!getTurtle(i)->getSide())
					{
						getTurtle(i)->setSide(true);
					}
					else
					{
						getTurtle(i)->turtle_reach_side();
						if (checksides(getTurtle(i)) == 1)
						{
							getTurtle(i)->set_heading(1);
						}
						else if (checksides(getTurtle(i)) == 2)
						{
							getTurtle(i)->set_heading(0);
						}
						getTurtle(i)->setSide(false);
					}
				} // to prevent turtle from going under the pipes above
				else if (turtle_hit_S_Pipe(getTurtle(i)) && (getTurtle(i)->get_heading() == 1 ))
				{
					getTurtle(i)->turtle_reach_side();
					getTurtle(i)->change_heading();
				}
					
				else if (turtle_hit_S_Pipe_Flipped(getTurtle(i)) && (getTurtle(i)->get_heading() == 0))
				{
					getTurtle(i)->turtle_reach_side();
					getTurtle(i)->change_heading();
				}

				//checks if the turtle collides with the pipes below
				//if it collides, teleports it to the upper pipes
				if (check_pipe_collision(getTurtle(i)) == 1)
				{
					getTurtle(i)->setPosition(Vector2f(sPipe->getPosition().x + 200.0f, sPipe->getPosition().y));
				}
				else if (check_pipe_collision(getTurtle(i)) == 2)
				{
					getTurtle(i)->setPosition(Vector2f(flippedSPipe->getPosition().x - 200.0f, flippedSPipe->getPosition().y));
				}

				//collision of turtles
				for (int j = i + 1; j < getTurtleSize(); j++)
				{
					//checks the collision between turtles
					if (checkCollusion(getTurtle(i), getTurtle(j)))
					{
						//changes the headings of the turtles
						if (collision[i])
						{
							turtleCollision[i].restart();
							getTurtle(i)->change_heading();
							getTurtle(j)->change_heading();
							getTurtle(i)->turtle_reach_side();
							getTurtle(j)->turtle_reach_side();
							collision[i] = false;
						}
						else
						{
							//marking the turtles collision array as true
							//to make them collide again after a 1000 milliseconds
							if (turtleCollision[i].getElapsedTime().asMilliseconds() > 1000)
							{
								collision[i] = true;
							}
						}
					}
				}
				//moves the turtles 
				getTurtle(i)->move(this->aggrevateRatio);
			}
			else
			{
				//no need to aggrevate death turtles so ratio = 1.0f
				getTurtle(i)->move(1.0f);
				//to delete the turtles (which are not alive) that fell out of bounds
				if (getTurtle(i)->getPosition().y > WINDOW_HEIGHT)
				{
					deleteTurtle(getTurtle(i));
				}
			}
		}


		//each 5 seconds turtle drops from a pipe
		//addition of the number of turtles in the game 
		//and the number of dead turtles cannot exceed 5
		if (clock.getElapsedTime().asSeconds() > 5 && getTurtleSize() + this->deathTurtleSize < 5)
		{
			addTurtle();
			clock.restart();
		}

		//sets the score of the game
		scoreboard->setScore(100 * this->deathTurtleSize);


		//initilazing the variables to use them in functions
		//marioFalling = true makes also onAir initiliazed below

		bool marioFalling = true;
		bool onAir;

		getMario()->move(); //makes mario move
		getMario()->decrease_X_velocity(); //decreasing X velocity when not pressed left/right

		//respawns Mario if it has lives and had fallen due to collusion
		if (getMario()->getPosition().y >= WINDOW_HEIGHT - 10.0f)
		{
			bool respawner = true;
			getMario()->respawn(respawner);
			getMario()->set_Y_velocity(MARIO_RESPAWN_SPEED);
		}
		else
		{
			bool respawner = false; 
			getMario()->respawn(respawner);
		}


		//checking if mario is falling
		//if it is falling mario can not move in x-axis
		if (getMario()->get_marker())
		{
			getMario()->set_X_velocity(0.0f);
			marioFalling = true;
		}
		else 
		{
			if (mario_checkBrickSides(getMario()))
			{
				//if mario is on bricksides this prevents to pass through it
				getMario()->set_X_velocity(0.0f);
			}

			if (mario_hitPipe(getMario()) || mario_hit_S_Pipe_Flipped(getMario()))
			{
				//pushes back if we hit pipes
				getMario()->set_X_velocity(-(MARIO_HORIZONTAL_SPEED / 4.0f));
			}

			if (mario_hitPipe_Flipped(getMario()) || mario_hit_S_Pipe(getMario()))
			{
				//pushes back if we hit pipes
				getMario()->set_X_velocity((MARIO_HORIZONTAL_SPEED / 4.0f));
			}

			if (mario_onFloor(getMario()) || mario_onBrick(getMario()))
			{
				//if mario is on floor or on brick mario falling is false
				//mario falling control whether we can jump or not
				//with this we can not double/triple or more jump
				marioFalling = false;
			}
			else if (mario_hitBottomBrick(getMario()))
			{
				//this prevents mario to pass through bricks from below
				//with not changing falling speed
				if (getMario()->get_Y_velocity() > MARIO_UNDER_BRICK_HIT_BACK_VALUE)
				{
					getMario()->set_Y_velocity(getMario()->get_Y_velocity());
					marioFalling = true;
				}
				else
				{
					getMario()->set_Y_velocity(MARIO_UNDER_BRICK_HIT_BACK_VALUE);
					marioFalling = true;
				}
			}
			else
			{
				marioFalling = true;
			}
		}

		if (marioFalling)
		{
			//if mario falling is true
			//on air is true 
			//if on air is true
			//we can not jump and we should update Y value
			onAir = true;
			getMario()->mario_jump(onAir);
			getMario()->velocity_Y_update();
		}
		else
		{
			//if mario falling is false
			//on air is false 
			//if on air is false
			//we can jump and we should still update Y value
			getMario()->set_Y_velocity(0.0f);
			onAir = false;
			getMario()->mario_jump(onAir);
		}

		//this function checks if mario is not falling 
		//we are checking mario and turtles position
		//if they are at two sides on the brick and have the same x-axis value
		//mario kills turtle
		if (!(getMario()->get_marker()))
		{
			if (mario_hitBottomBrick(getMario())) //mario hit from bottom and turtle still dies
			{
				for (int i = 0; i < getTurtleSize(); i++)
				{
					if (!(getTurtle(i)->get_marker()))
					{
						float mario_top = getMario()->getPosition().y - getMario()->getGlobalBounds().height;
						float mario_right = getMario()->getPosition().x + getMario()->getGlobalBounds().width;
						float mario_left = getMario()->getPosition().x - getMario()->getGlobalBounds().width;
						float turtle_bot = getTurtle(i)->getPosition().y + (getTurtle(i)->getGlobalBounds().height / 2.0f);
						float turtle_left = getTurtle(i)->getPosition().x - (getTurtle(i)->getGlobalBounds().width / 2.0f);
						float turtle_right = getTurtle(i)->getPosition().x + (getTurtle(i)->getGlobalBounds().width / 2.0f);
						float turtle_top = getTurtle(i)->getPosition().y - (getTurtle(i)->getGlobalBounds().height / 2.0f);
						float tolerance = 5.0f;
						if ((mario_right + tolerance >= turtle_left)
							&& (mario_left - tolerance <= turtle_right)
							&& (mario_top - turtle_bot <= (brick_vec[0]->getGlobalBounds().height * 1.1f))
							&& (turtle_top < mario_top))
						{
							getTurtle(i)->fall();
							this->deathTurtleSize++; //updates turtledeaths
							break;
						}
					}
				}
			}
		}


		//this function checks collusion between mario and turtle
		//if the collusion happens when mario is on top 
		//mario kills turtle
		//if the collusion happens when mario is near or under turtle
		//turtle kills mario
		for (int i = 0; i < getTurtleSize(); i++)
		{
			if (!(getTurtle(i)->get_marker()) && !(getMario()->get_marker()))
			{
				if (checkCollusion(getMario(), getTurtle(i)))
				{
					float mario_top = getMario()->getPosition().y - getMario()->getGlobalBounds().height;
					float mario_bot = getMario()->getPosition().y;
					float turtle_top = getTurtle(i)->getPosition().y - getTurtle(i)->getGlobalBounds().height;
					float turtle_bot = getTurtle(i)->getPosition().y + getTurtle(i)->getGlobalBounds().height;
					float mario_right = getMario()->getPosition().x + getMario()->getGlobalBounds().width;
					float mario_left = getMario()->getPosition().x - getMario()->getGlobalBounds().width;
					float turtle_left = getTurtle(i)->getPosition().x - (getTurtle(i)->getGlobalBounds().width / 2.0f);
					float turtle_right = getTurtle(i)->getPosition().x + (getTurtle(i)->getGlobalBounds().width / 2.0f);
					float tolerance = 35.0f;
					if ((mario_bot >= turtle_top - tolerance)
						&& (mario_bot <= turtle_top + tolerance))
					{
						getTurtle(i)->fall();
						this->deathTurtleSize++;
						break;
					}
					else
					{
							
						getMario()->fall();
						scoreboard->setLives(scoreboard->getLives() - 1); //sets lives of mario
						break;
					}
				}
			}
		}
		//sleeps the system for better animation
		sf::sleep((milliseconds(900 / SPEED)));
	}
}