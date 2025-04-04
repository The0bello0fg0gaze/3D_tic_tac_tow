#include <cmath>
#include <iostream>
#include <vector>
#include "raylib.h"
#include "rcamera.h"
using namespace std;
Vector3 rectpos = {1.0f, 1.0f, 1.0f};
vector<int> relative={3,2,1};
void DisplayMap(vector<vector<vector<int>>> &map);
void UpdateRelative(int move,int mode, Camera &camera);
void SetPos(Camera &camera);
void MoveBlock(int move,int cpos,int mode);
void SetBock(vector<vector<vector<int>>> &map);
void MoveBlock(int move, Camera camera){
    vector<float> tempview = {0,0,0}; 
    if((move == 1)){ // left 
        rectpos.x += -1; 
    }else if((move == -1)){ // right 
        rectpos.x += 1;
    }else if((move == 2)){ // up
        rectpos.y += 1;
    }else if((move == -2)){ // down
        rectpos.y += -1;
    }else if((move == 3)){ //out
        rectpos.z += 1;
    }else if((move == -3)){ //in
        rectpos.z += -1;
    }
}


void DisplayMap(vector<vector<vector<int>>> &map){
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
}

void SetPos(Camera &camera){
    int set = relative.at(0);
    if(set == 1){
        camera.position = (Vector3){6.0f,1.0f,1.0f};
    }else if(set == 2){
        camera.position = (Vector3){1.0f,6.0f,1.0f};
    }else if(set == 3){
        camera.position = (Vector3){1.0f,1.0f,6.0f};
    }
    else if(set == -1){
        camera.position = (Vector3){-4.0f,1.0f,1.0f};
    }else if(set == -2){
        camera.position = (Vector3){1.0f,-4.0f,1.0f};
    }else if(set == -3){
        camera.position = (Vector3){1.0f,1.0f,-4.0f};
    }
}
void UpdateRelative(int move,int mode, Camera &camera){
    if((move == 1)){                                        //camera.up movement manager 
        vector<float> up = {0.0f, 0.0f, 0.0f};
        float temp1 = relative.at(0);
        if(0<temp1){up.at((temp1)-1) = -1;}
        else{up.at((0-temp1)-1) = 1;}
        camera.up = (Vector3) {up[0],up[1],up[2]};
    }
    if((move <= 2)&&(move >= 1)&&(mode == 0)){
        int temp = relative.at(0);
        relative.at(0) = relative.at(move);
        relative.at(move) = 0-temp;
    }
    else if((move <= 2)&&(move >= 1)&&(mode == 1)){
        int temp = relative.at(move);
        relative.at(move) = relative.at(0);
        relative.at(0) = 0-temp;
    }
}



int main(void)
{
    vector<vector<vector<int>>> map(3,vector<vector<int>>(3,vector<int>(3,0))); // the map of the cube we will be using
    int player = 1;
    int move = 1; 
    int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib 3D Tic Tac Tow Game (PVE)");

    // Define the camera to look into our 3d world (position, target, up vector)
    Camera camera = { 0 };
    camera.position = (Vector3){ 1.1f, 1.0f, 6.0f };  // Camera position
    camera.target = (Vector3){ 1.0f, 1.0f, 1.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    int cameraMode = CAMERA_FIRST_PERSON;

    SetTargetFPS(30);                   // Set our game to run at 60 frames-per-second
    while(!WindowShouldClose()){
        UpdateCamera(&camera,0);
        if(IsKeyPressed(KEY_UP)){          //Movement of the camera (Map)
            UpdateRelative(1,0,camera);
            SetPos(camera);
        }else if(IsKeyPressed(KEY_DOWN)){
            UpdateRelative(1,1,camera);
            SetPos(camera);
        }else if(IsKeyPressed(KEY_RIGHT)){
            UpdateRelative(2,0,camera);
            SetPos(camera);
        }else if(IsKeyPressed(KEY_LEFT)){
            UpdateRelative(2,1,camera);
            SetPos(camera);
        }
        if(IsKeyPressed(KEY_A)){             // Movement for player Character
            MoveBlock(1 ,camera); //left
        }else if(IsKeyPressed(KEY_D)){
            MoveBlock(-1 ,camera); //right
        }else if(IsKeyPressed(KEY_W)){
            MoveBlock(2 ,camera); //Up
        }else if(IsKeyPressed(KEY_S)){
            MoveBlock(-2 ,camera); //Down
        }else if(IsKeyPressed(KEY_Q)){
            MoveBlock(3 ,camera); //Down
        }else if(IsKeyPressed(KEY_E)){
            MoveBlock(-3 ,camera); //Down
        }else if(IsKeyPressed(KEY_SPACE)){
            map[rectpos.x][rectpos.y][rectpos.z] = player;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
                BeginMode3D(camera); // Start 3D mode
                    DisplayMap(map);
                    DrawCube(rectpos, 0.5f, 0.5f, 0.5f, BLACK);
                EndMode3D(); // End 3D mode
                DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", camera.position.x, camera.position.y, camera.position.z), 610, 60, 10, BLACK);
                DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", camera.target.x, camera.target.y, camera.target.z), 610, 30, 10, BLACK);
                DrawText("Press ESC to close", 10, 10, 20, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}