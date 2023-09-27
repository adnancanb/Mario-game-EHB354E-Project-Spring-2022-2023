#include "Common.h"
#include "Object.h"
#include "Floor.h"
#include "Brick.h"
#include "Turtle.h"
#include "Pipe.h"
#include "PipeFlipped.h"
#include "SPipe.h"
#include "SPipeFlipped.h"
#include "mario.h"
#include "Scoreboard.h"

class Game
{
	RenderWindow* window;
	Font font;
	Text text;
	Floor* floor;
	Pipe* pipe;
	SPipe* sPipe;
	FlippedPipe* flippedPipe;
	FlippedSPipe* flippedSPipe;
	ScoreBoard *scoreboard;
	Brick* brick_vec[7];
	int speed;
	Object* object;
	int listSize;
	Clock clock;
	Clock turtle_death;
	int deathTurtleSize;
	float aggrevateRatio;
	Clock aggrevation;
	Clock turtleCollision[5];

public:
	Game(int);
	int update(void);
	void drawBackground(RenderWindow&);
	bool onFloor(Object*);
	int checksides(Object*);
	int check_pipe_collision(Object*);
	bool mario_onFloor(Object*);
	bool mario_onBrick(Object*);
	bool mario_hitBottomBrick(Object*);
	bool mario_checkBrickSides(Object*);
	bool mario_hitPipe(Object*);
	bool mario_hitPipe_Flipped(Object*);
	bool mario_hit_S_Pipe(Object*);
	bool mario_hit_S_Pipe_Flipped(Object*);
	bool turtle_hit_S_Pipe(Object*);
	bool turtle_hit_S_Pipe_Flipped(Object*);
	bool checkCollusion(Object*, Object*);

	Mario* addMario(void);
	Turtle* addTurtle(void);
	Object* getTurtle(int index);
	void deleteTurtle(Object*);
	Object* getMario(void);
	int getTurtleSize(void);

	void endGameDisplay(bool, RenderWindow&);
};
