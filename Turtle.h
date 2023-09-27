#pragma once
#include "Common.h"
#include "Object.h"

class Turtle :public Object
{
	float vx;
	float vy;
	bool side_check;
	bool down;
	bool death_marker;
	Clock clock;
public:
	Turtle();
	void move(float);
	void jump(void);
	void fall(void);

	bool get_marker(void);
	void state_diagram(void);
	void turtle_reach_side(void);
	void set_heading(int);
	int get_heading(void);
	void change_heading(void);
	bool getSide(void);
	void setSide(bool);
	void setDown(bool);
	
};


