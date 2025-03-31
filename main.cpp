#include <cmath>
#include <iostream>
#include <vector>
#include "raylib.h"
#include "rcamera.h"
using namespace std;
vector<int> relative={3,2,1};
void UpdateRelative(int move,int mode, Camera &camera);
void SetPos(Camera &camera);

void SetPos(Camera &camera){
    int set = relative.at(0);
    if(set == 1){
        camera.position = (Vector3){6.1f,1.0f,1.0f};
    }else if(set == 2){
        camera.position = (Vector3){1.1f,6.0f,1.0f};
    }else if(set == 3){
        camera.position = (Vector3){1.1f,1.0f,6.0f};
    }
    else if(set == -1){
        camera.position = (Vector3){-4.1f,1.0f,1.0f};
    }else if(set == -2){
        camera.position = (Vector3){1.1f,-4.0f,1.0f};
    }else if(set == -3){
        camera.position = (Vector3){1.1f,1.0f,-4.0f};
    }
}
void UpdateRelative(int move,int mode, Camera &camera){
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
    vector<vector<vector<int>>> map(3,vector<vector<int>>(3,vector<int>(3,0)));
    int move = 1; 
    int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");

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
        if(IsKeyPressed(KEY_UP)){
            UpdateRelative(1,0,camera);
            SetPos(camera);
            std::cout<<camera.position.x<<"/"<<camera.position.y<<"/"<<camera.position.z<<std::endl;
        }else if(IsKeyPressed(KEY_DOWN)){
            UpdateRelative(1,1,camera);
            SetPos(camera);
            std::cout<<camera.position.x<<"/"<<camera.position.y<<"/"<<camera.position.z<<std::endl;
        }else if(IsKeyPressed(KEY_RIGHT)){
            UpdateRelative(2,0,camera);
            SetPos(camera);
            std::cout<<camera.position.x<<"/"<<camera.position.y<<"/"<<camera.position.z<<std::endl;
        }else if(IsKeyPressed(KEY_LEFT)){
            UpdateRelative(2,1,camera);
            SetPos(camera);
            std::cout<<camera.position.x<<"/"<<camera.position.y<<"/"<<camera.position.z<<std::endl;
        }else if(IsKeyPressed(KEY_A)){
            camera.up = (Vector3){1,0,0};
        }else if(IsKeyPressed(KEY_S)){
            camera.up = (Vector3){0,1,0};
        }else if(IsKeyPressed(KEY_D)){
            camera.up = (Vector3){0,0,1};
        }
        map[1][0][0]=-1;
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