#include <cmath>
#include <iostream>
#include <vector>
#include "raylib.h"
#include "rcamera.h"
using namespace std;
vector<int> relative={3,2,1};
void UpdateRelative(int move);
void SetPos(Vector3 &pos);

void SetPos(Vector3 &pos){
    int set = relative.at(0);
    if(set == 1){
        pos = (Vector3){6.1f,1.1f,1.1f};
    }else if(set == 2){
        pos = (Vector3){1.1f,6.1f,1.1f};
    }else if(set == 3){
        pos = (Vector3){1.1f,1.1f,6.1f};
    }
    else if(set == -1){
        pos = (Vector3){-6.1f,1.1f,1.1f};
    }else if(set == -2){
        pos = (Vector3){1.1f,-6.1f,1.1f};
    }else if(set == -3){
        pos = (Vector3){1.1f,1.1f,-6.1f};
    }
}
void UpdateRelative(int move){
    if((move >= 2)&&(move <= 1)){
        int temp = relative.at(0);
        relative.at(0) = relative.at(move);
        relative.at(move) = 0-temp;
    }
}

int main(void)
{
    vector<vector<vector<int>>> map(3,vector<vector<int>>(3,vector<int>(3,0)));
    Vector3 pos = { 1.1f, 1.1f, 6.1f };
    int move = 1; 
    int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");

    // Define the camera to look into our 3d world (position, target, up vector)
    Camera camera = { 0 };
    camera.position = pos;  // Camera position
    camera.target = (Vector3){ 1.0f, 1.0f, 1.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    int cameraMode = CAMERA_FIRST_PERSON;

    SetTargetFPS(30);                   // Set our game to run at 60 frames-per-second
    while(!WindowShouldClose()){
        UpdateCamera(&camera,0);
        if(IsKeyUp(KEY_UP)){
            UpdateRelative(1);
            SetPos(pos);
            std::cout<<pos.x<<pos.y<<pos.z<<std::endl;
        }else if(IsKeyUp(KEY_DOWN)){
            UpdateRelative(2);
            SetPos(pos);
            std::cout<<pos.x<<pos.y<<pos.z<<std::endl;
        }
        camera.position = pos;
        BeginDrawing();
        ClearBackground(RAYWHITE);
                BeginMode3D(camera); // Start 3D mode
                    for(float x=0; x<3; x++){
                        for(float y=0; y<3; y++){
                            for(float z=0; z<3; z++){
                                DrawCubeWires(Vector3 {x,y,z}, 1.0f, 1.0f, 1.0f, BLACK);
                                if(map[x][y][z] == 1){
                                    DrawCube(Vector3 {x,y,z}, 0.5f, 0.5f, 0.5f, RED);
                                }
                                else if(map[x][y][z] == -1){
                                    DrawCube(Vector3 {x,y,z}, 0.5f, 0.5f, 0.5f, BLUE);
                                }
                            }
                        }
                    }   
                EndMode3D(); // End 3D mode
                DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", camera.position.x, camera.position.y, camera.position.z), 610, 60, 10, BLACK);
                DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", camera.target.x, camera.target.y, camera.target.z), 610, 30, 10, BLACK);
                DrawText("Press ESC to close", 10, 10, 20, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}