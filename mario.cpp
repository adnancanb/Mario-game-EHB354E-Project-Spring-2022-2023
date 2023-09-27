#include "Mario.h"



Mario::Mario() {
    //loading mario texture
    marioTexture.loadFromFile("../Matrix_Hüner_OOP_Project/assets/mario1.png");
    sprite.setTexture(marioTexture);
    marioWidth = sprite.getTextureRect().width;
    marioHeight = sprite.getTextureRect().height;
    sprite.setOrigin(marioWidth / 2, marioHeight); //setting mario's origin
    sprite.setScale(0.825f, 0.825f); //setting mario's size for better experience

    //uploading mario2.png, mario3.png and mario4.png
    //for moving effect
    marioTextureMovementEffect[0].loadFromFile("../Matrix_Hüner_OOP_Project/assets/mario2.png");
    marioTextureMovementEffect[1].loadFromFile("../Matrix_Hüner_OOP_Project/assets/mario3.png");
    marioTextureMovementEffect[2].loadFromFile("../Matrix_Hüner_OOP_Project/assets/mario4.png");

    //initiliazing clock to implement moving effect with using clock 
    clock.restart();

    //initiliazing Vx and Vy velocities
    this->vx = 0;
    this->vy = 0;

    //initilizing mario's position
    sprite.setPosition(Vector2f(float(WINDOW_WIDTH / 2.0f), float(WINDOW_HEIGHT - 70.0f)));

    //initiliazing variables
    int currentTextureIndex = 0;
    bool death_marker = false;

};


void Mario::move() {

    //this funciton makes mario move horizontally 
    //and sets move(vx, 0)
    sprite.move(this->vx, 0);

  
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
        || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
        {

        if (clock.getElapsedTime().asMilliseconds() >= TIMESTEP * 10) {
            
            //this loop makes moving effect
            currentTextureIndex = (currentTextureIndex + 1) % 3;

            sprite.setTexture(marioTextureMovementEffect[currentTextureIndex]);

            clock.restart();

        }

        sprite.setScale(0.825f, 0.825f);

        this->vx = -MARIO_HORIZONTAL_SPEED;

    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
            || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {

        //this is the same loop
        if (clock.getElapsedTime().asMilliseconds() >= (TIMESTEP * 10)) {

            currentTextureIndex = (currentTextureIndex + 1) % 3;
            sprite.setTexture(marioTextureMovementEffect[currentTextureIndex]);
            clock.restart();

        }

        //this scale(-a, a) makes the heading
        sprite.setScale(-0.825f, 0.825f);
        this->vx = (MARIO_HORIZONTAL_SPEED);

    }

    else 
    {
        //else if not pressed and mario is slowing with decrease_X_velocity
        //this codeline makes sliding effect
        this->vx = vx;
        if (abs(vx) < abs(MARIO_HORIZONTAL_SPEED) && abs(vx) > 0.5f) 
        {
            marioTexture.loadFromFile("../Matrix_Hüner_OOP_Project/assets/mario5.png");
            sprite.setTexture(marioTexture);
        }
        if (abs(vx) <= 0.5f)
        {
            marioTexture.loadFromFile("../Matrix_Hüner_OOP_Project/assets/mario1.png");
            sprite.setTexture(marioTexture);
        }
    }

    //FOR MARIO TO STAY IN THE MAP

    if (sprite.getPosition().y < sprite.getTextureRect().height) {

        sprite.setPosition(sprite.getPosition().x, sprite.getTextureRect().height);

    };

    if (sprite.getPosition().x < (sprite.getTextureRect().width / 2)) {

        sprite.setPosition(sprite.getTextureRect().width / 2, sprite.getPosition().y);

    };

    if (sprite.getPosition().y > WINDOW_HEIGHT) {

        sprite.setPosition(sprite.getPosition().x, WINDOW_HEIGHT);

    };

    if (sprite.getPosition().x > WINDOW_WIDTH - (sprite.getTextureRect().width / 2)) {

        sprite.setPosition(WINDOW_WIDTH - (sprite.getTextureRect().width / 2), sprite.getPosition().y);

    };

};


void Mario::decrease_X_velocity()
{
    //decreasing X velocity when not pressed any button
    this->vx *= 0.8f;
}



void Mario::mario_jump(bool onAir)
{
    //makes mario to jump if mario is not on the air
    if (!onAir) 
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            this->vy = MARIO_JUMP_HEIGHT;
        }
    }
    else
    {
        //if mario is on air and falling due to turtle
        //this makes the death animation
        if (death_marker)
        {
            marioTexture.loadFromFile("../Matrix_Hüner_OOP_Project/assets/mario7.png");
            sprite.setTexture(marioTexture);
        }
        else
        {
            //if it is not due to turtle
            //this makes the jumping animation
            marioTexture.loadFromFile("../Matrix_Hüner_OOP_Project/assets/mario6.png");
            sprite.setTexture(marioTexture);
        }
    }
    sprite.move(0, vy);
}

void Mario::set_Y_velocity(float vy)
{
    //this is setting Vy velocity for mario
    this->vy = vy;

}

void Mario::set_X_velocity(float vx)
{
    //this is setting Vx velocity for mario
    this->vx = vx;
}

float Mario::get_Y_velocity(void)
{
    //this is getting Vy velocity for mario
     return vy;
}

//this function makes mario to fall when turtle collides mario
void Mario::fall(void)
{
    this->vx = 0.0f;
    this->vy = MARIO_DEATH_SPEED;
    marioTexture.loadFromFile("../Matrix_Hüner_OOP_Project/assets/mario7.png");
    sprite.setTexture(marioTexture);
    this->death_marker = true;
}

//this function respawns mario if we have extra lives
//and sets its position to initiliaze
void Mario::respawn(bool respawn)
{
    if (respawn)
    {
        sprite.setPosition((WINDOW_WIDTH / 2.0f), 200.0f);
        this->death_marker = false;
    }
}

//gets death_marker
bool Mario::get_marker()
{
    return this->death_marker;
}
