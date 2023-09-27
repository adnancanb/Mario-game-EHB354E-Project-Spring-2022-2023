#pragma once
#include "Common.h"

class Object {
	Object* next;
	friend class Game;
protected: //for inheritance 
	Texture textures[8];
	Sprite sprite;
	Vector2f pos;
	int state;
	int heading; //direction it is headed
	float vx, vy;

public:
	//abstract class does not need a constructor!
	Object()
	{
		next = NULL;
	}
	//abstract destructor (virtual)
	virtual ~Object()
	{

	}
	void setPosition(Vector2f pos);
	Vector2f getPosition(void);
	void draw(RenderWindow& window);
	float findWidth();
	float findHeight();
	IntRect boundingBox(void);
	FloatRect getGlobalBounds(void);
	void velocity_Y_update(void);

	//Abstract Methods that will be overriden
	//we need polymorphism here (virtual)
	virtual void move(void);
	virtual void move(float);
	virtual void jump(void);
	virtual void mario_jump(bool);
	virtual void fall(void);	
	virtual void respawn(bool);
	virtual void decrease_X_velocity(void);
	virtual void set_Y_velocity(float);
	virtual float get_Y_velocity(void);
	virtual void set_X_velocity(float);
	virtual bool get_marker(void);
	virtual bool get_marker(bool);
	virtual void state_diagram(void);
	virtual void turtle_reach_side(void);
	virtual void turtle_teleport(Vector2f);
	virtual void set_heading(int);
	virtual int get_heading(void);
	virtual void change_heading(void);
	virtual bool getSide(void);
	virtual void setSide(bool);
	virtual void setDown(bool);
	virtual void aggrevate(void);
};
