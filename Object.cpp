#include "Object.h"


//Abstract methods does not need a body!
//(for polymorphism)

void Object::move(float vx)
{

}

void Object::move() 
{
	
}

void Object::jump(void)
{

}

void Object::mario_jump(bool onAir)
{

}

void Object::fall()
{

}

void Object::respawn(bool respawn)
{

}

void Object::decrease_X_velocity()
{

}

void Object::set_Y_velocity(float vy)
{

}

float Object::get_Y_velocity(void)
{
	return vy;
}


void Object::set_X_velocity(float vx)
{

}

bool Object::get_marker()
{
	return true;
}

bool Object::get_marker(bool marker)
{
	return marker;
}


void Object::state_diagram()
{

}

void Object::turtle_reach_side()
{

}

void Object::turtle_teleport(Vector2f pos)
{

}

void Object::set_heading(int heading)
{

}

int Object::get_heading()
{
	return 0;
}

void Object::change_heading(void)
{

}

bool Object::getSide()
{
	return true;
}

void Object::setSide(bool side)
{

}

void Object::setDown(bool down)
{

}

void Object::aggrevate()
{

}


//updating the Vy velocity
void Object::velocity_Y_update()
{
	this->vy += (G * TIMESTEP) / 1000.0f;
}

//setting the position
void Object::setPosition(Vector2f pos)
{
	this->pos = pos;
	sprite.setPosition(pos);
}
//drawing the sprite into the screen
void Object::draw(RenderWindow& window)
{
	window.draw(sprite);
}
//getting the position
Vector2f Object::getPosition()
{
	return sprite.getPosition();
}

//return the bounding box of the sprite
IntRect Object::boundingBox()
{
	return sprite.getTextureRect();
}

//getting the global bounds of the object
FloatRect Object::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}

//getting the width and the hegiht of the sprite
float Object::findWidth() {
	float width = sprite.getTextureRect().width;
	return width;
}

float Object::findHeight() {
	float height = sprite.getTextureRect().height;
	return height;
}