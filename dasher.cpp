#include "raylib.h"
#include <iostream>

using namespace std;

int main() 
{

//Window dimensions
const int windowWidth{512};
const int windowHeight{380};

//Is the rectangle in air ?
bool isInAir{false};

// Jump veocity (Pixels/Second)
const int jumpVal{-600};

//Acceleratie due to gravity (pixels/frame)/frame
const int gravity{1'000};

//Initialize the window
InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

// scarfi variables
Texture2D scarfy = LoadTexture("textures/scarfy.png");
Rectangle scarfiRec;
scarfiRec.width = scarfy.width/6;
scarfiRec.height = scarfy.height;
scarfiRec.x = 0;
scarfiRec.y = 0;
Vector2 scarfyPos;
scarfyPos.x = windowWidth/2 - scarfiRec.width/2;
scarfyPos.y = windowHeight - scarfiRec.height;


// nebula variables
Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
Vector2 nebPos{windowWidth, windowHeight- nebRec.height};

int nebVel{-600};

// animation frame
int frame{};

// amount of time before we update the animation frame
const float updateTime{1.0/12.0};
float runningTime{};

int velocity(0);

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {

    // delta time (time since last frame)
    const float dT{GetFrameTime()};
    
        //Start drawing
        BeginDrawing();
            ClearBackground(WHITE);

            //performe a ground check
            if(scarfyPos.y >= windowHeight - scarfiRec.width  ) //Rectangle is on the ground
            {
                //Reset velocity
                velocity = 0;
                isInAir = false;
            }
            else //Rectangle is the air
            {
                //Apply gravity
                velocity += gravity * dT;
                isInAir = true;
            }

            //Jump Action check
            if(IsKeyPressed(KEY_SPACE) && !isInAir)
            {
                velocity += jumpVal;
            }

            //update nebula position
            nebPos.x += nebVel * dT;
            
            //update scarfy position
            scarfyPos.y += velocity * dT;

            if(!isInAir)
            {

                //update running time
                runningTime += dT;
                if(runningTime >= updateTime)
                {
                    runningTime = 0.0;
                    //Update animation frame
                    scarfiRec.x = frame * scarfiRec.width;
                    frame++;
                    if(frame > 5)
                    {
                     frame = 0;
                    }
               }
            }


           
           //draw nebula
           DrawTextureRec(nebula, nebRec, nebPos, WHITE);

           //draw scarfy
           DrawTextureRec(scarfy, scarfiRec, scarfyPos, WHITE);

        //Stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}