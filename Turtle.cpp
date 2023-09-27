#include "Turtle.h"


Turtle::Turtle()//constructor for turtle
{
	char path[64];
	for (int i = 0; i < 5; i++) {
		sprintf(path, "../Matrix_Hüner_OOP_Project/assets/turtle%d.png", (i + 1));
		textures[i].loadFromFile(path);
	}
	sprite.setTexture(textures[0]);
	sprite.setOrigin(sprite.getTextureRect().width / 2.0f, sprite.getTextureRect().height / 2.0f);
	sprite.setPosition(Vector2f(200, 160));
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setScale(0.75f, 0.75f); //downscaling the sprite
	//initializing the attributes
	this->vx = TURTLE_VX;
	this->vy = 0;
	this->heading = 0;
	this->state = 0;
	this->side_check = false;
	this->down = false;
	this->death_marker = false;

	//initializing the clock for the smoother animation
	clock.restart();
}

//moves the sprite
void Turtle::move(float ratio)
{
	if (this->vy == 0)
	{
		sprite.move(this->vx * ratio, this->vy);
	}
	else if (this->vy != 0)
	{
		//if the turtle is falling to a floor
		//Vx is reduced
		sprite.move(this->vx * 0.5f, this->vy);
	}
}

//sets the Vy velocities depending on
//if its on floor
//or if its falling to a surface
void Turtle::jump()
{
	if (!(this->down))
	{
		this->vy = 0.0f;
	}
	else
	{
		this->vy = TURTLE_FALL_VY;
	}
}

//falling animation initialization
void Turtle::fall()
{
	this->vx = 0.0f;
	this->vy = TURTLE_DEATH_SPEED;
	sprite.setTexture(textures[4]);
	this->death_marker = true; //marking the turtleas dead
}

//gets the marker for if the turtle is dead or alive
bool Turtle::get_marker()
{
	return this->death_marker;
}

//if the turtle reaches a side
//Vx = -Vx
void Turtle::turtle_reach_side()
{
	this->vx = -this->vx;
}
//sets the heading
void Turtle::set_heading(int heading)
{
	this->heading = heading;
}
//gets the heading
int Turtle::get_heading()
{
	return this->heading;
}
//changes the heading
void Turtle::change_heading()
{
	if (this->heading == 0)
	{
		this->heading = 1;
	}
	else if (this->heading == 1)
	{
		this->heading = 0;
	}
}

//initial state is 0
//state diagram for turtle animation
void Turtle::state_diagram()
{
	//clock is applied for a smoother animation
	//explained more in the report
	if (clock.getElapsedTime().asMilliseconds() >= (TIMESTEP * 1.35))
	{
		switch (this->state)
		{
		case 0:
			sprite.setTexture(textures[this->state]);
			sprite.setScale(0.75f, 0.75f);
			if (this->vx == 0 && this->heading == 0)
			{
				this->state = 0;
			}
			else if (this->vx != 0 && this->heading == 0)
			{
				this->state = 1;
			}
			else if (this->heading == 1)
			{
				this->state = 3;
			}

			break;
		case 1:
			sprite.setTexture(textures[this->state]);
			sprite.setScale(0.75f, 0.75f);
			if (this->vx != 0 && this->heading == 0)
			{
				this->state = 2;
			}
			else if (this->vx == 0 && this->heading == 0)
			{
				this->state = 0;
			}
			else if (this->heading == 1)
			{
				this->state = 3;
			}
			break;
		case 2:
			sprite.setTexture(textures[this->state]);
			sprite.setScale(0.75f, 0.75f);
			if (this->heading == 0)
			{
				this->state = 0;
			}
			else if (this->heading == 1)
			{
				this->state = 3;
			}
			break;
		case 3:
			sprite.setTexture(textures[(this->state) - 3]);
			sprite.setScale(-0.75f, 0.75f);
			if (this->vx == 0 && this->heading == 1)
			{
				this->state = 3;
			}
			else if (this->vx != 0 && this->heading == 1)
			{
				this->state = 4;
			}
			else if (this->heading == 0)
			{
				this->state = 0;
			}
			break;
		case 4:
			sprite.setTexture(textures[(this->state) - 3]);
			sprite.setScale(-0.75f, 0.75f);
			if (this->vx != 0 && this->heading == 1)
			{
				this->state = 5;
			}
			else if (this->heading == 0)
			{
				this->state = 0;
			}
			break;
		case 5:
			sprite.setTexture(textures[(this->state) - 3]);
			sprite.setScale(-0.75f, 0.75f);
			if (this->heading == 1)
			{
				this->state = 3;
			}
			else if (this->heading == 0)
			{
				this->state = 0;
			}
			break;
		}
		clock.restart();
	}
	
}
//getting the side
bool Turtle::getSide()
{
	return side_check;
}
//setting the side
void Turtle::setSide(bool side_check)
{
	this->side_check = side_check;
}
//sets bool down attribute
//this attribute is true if the turtle
//is not on any surface
//its false if its on any surface
void Turtle::setDown(bool down)
{
	this->down = down;
}

