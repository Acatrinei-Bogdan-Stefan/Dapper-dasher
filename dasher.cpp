#include "raylib.h"
#include <iostream>

using namespace std;

int main() 
{

//Window dimensions
const int windowWidth{512};
const int windowHeight{380};

// Rectagle dimensions
const int width{50};
const int height{80};

//Is the rectangle in air ?
bool isInAir{false};

// Jump veocity
const int jumpVal{-22};

//Acceleratie due to gravity (pixels/frame)/frame
const int gravity{1};

int posY{windowHeight - height};
int velocity(0);

//Initialize the window
InitWindow(windowWidth, windowHeight, "Dapper Dasher!");


    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        //Start drawing
        BeginDrawing();
            ClearBackground(WHITE);

            //performe a ground check
            if(posY >= windowHeight - height  ) //Rectangle is on the ground
            {
                //Reset velocity
                velocity = 0;
                isInAir = false;
            }
            else //Rectangle is the air
            {
                //Apply gravity
                velocity += gravity;
                isInAir = true;
            }

            //Jump Action check
            if(IsKeyPressed(KEY_SPACE) && !isInAir)
            {
                velocity += jumpVal;
            }
            
            //update position
            posY += velocity;

            DrawRectangle(windowWidth/2, posY, width, height, BLUE);

        //Stop drawing
        EndDrawing();
    }
    CloseWindow();
}