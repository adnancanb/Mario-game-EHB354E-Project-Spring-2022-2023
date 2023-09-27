#define _CRT_SECURE_NO_WARNINGS
#define SFML_NO_DEPRECATED_WARNINGS //to use setColor method
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;
using namespace sf;

//parameter macros
#define WINDOW_WIDTH    960
#define WINDOW_HEIGHT   900
#define SPEED		    30
#define TIMESTEP		1100.0f / SPEED 
#define FIRST_BRICK_HEIGHT 294.0f
#define TURTLE_VX		5.0f
#define TURTLE_FALL_VY  11.0f
#define G				15.0f
#define MARIO_HORIZONTAL_SPEED	8.0f
#define MARIO_JUMP_HEIGHT		-15.0f
#define MARIO_UNDER_BRICK_HIT_BACK_VALUE 2.0f
#define MARIO_RESPAWN_SPEED -5.0f
#define TURTLE_DEATH_SPEED 10.0f
#define MARIO_DEATH_SPEED 5.0f

