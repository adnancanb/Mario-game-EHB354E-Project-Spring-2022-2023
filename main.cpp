#include "Game.h"
#include "menu.h"

//main loop to run the program
int main()
{
    //switch case for making the connection between the game 
    //and the main menu
    int check = 0;

    while (true)
    {
        switch (check)
        {
        case(1):
        { 
            sf::sleep(milliseconds(100));
            Game* game = new Game(SPEED);
            check = game->update();//return 0 if the user presses enter
            //returns 2 if the user presses exit
            delete game;//deleting the game object to have no memory leak
        }
            break;
        case(0):
        {
            Menu* menu = new Menu();
            check = menu->MainMenu();//returns 1 if the game ends
            //returns 0 if the user presses exit
            delete menu;//deleting the menu object to have no memory leak
        }
            break;
        case(2):
            //exits the game
            return 0;
            break;
        }
    }
}
