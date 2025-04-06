#include <cmath>
#include <iostream>
#include <vector>
#include "raylib.h"
#include "rcamera.h"
#include "math.h"
using namespace std;
Vector3 rectpos = {1.0f, 1.0f, 1.0f};
vector<int> relative={3,2,1};
void DisplayMap(vector<vector<vector<int>>> &map);
void UpdateRelative(int move,int mode, Camera &camera);
void SetPos(Camera &camera);
void MoveBlock(int move, Camera camera);
int GameState(vector<vector<vector<int>>> map);

int GameState(vector<vector<vector<int>>> map){
    int lx,ly,lz;
    for(int x=0; x<3; x++){
        for(int y=0; y<3; y++){
            for(int z=0; z<3; z++){
                if(map[x][y][z] == 1){
                    lz++;
                }else if(map[x][y][z] == -1){
                    lz--;
                }

                if(map[x][z][y] == 1){
                    ly++;
                }else if(map[x][z][y] == -1){
                    ly--;
                }

                if(map[z][y][x] == 1){
                    lx++;
                }else if(map[z][y][x] == -1){
                    lx--;
                }

            }
            if((lx == 3)||(ly == 3)||(lz == 3)){
                return 1;
            }else if((lx == -3)||(ly == -3)||(lz == -3)){
                return -1;
            }
            lx = 0;ly = 0; lz = 0;
        }
    }
    return 0;    
}

void MoveBlock(int move, Camera camera){
    vector<float> tempview = {0,0,0}; 
    if((move == 1)&&(rectpos.x < 3)&&(rectpos.x > 0)){ // left 
        rectpos.x -= 1; 
    }else if((move == -1)&&(rectpos.x < 2)&&(rectpos.x >= 0)){ // right 
        rectpos.x += 1;
    }else if((move == 2)&&(rectpos.y < 2)&&(rectpos.y >= 0)){ // up
        rectpos.y += 1;
    }else if((move == -2)&&(rectpos.y < 3)&&(rectpos.y > 0)){ // down
        rectpos.y -= 1;
    }else if((move == 3)&&(rectpos.z < 2)&&(rectpos.z >= 0)){ //out
        rectpos.z += 1;
    }else if((move == -3)&&(rectpos.z < 3)&&(rectpos.z > 0)){ //in
        rectpos.z -= 1;
    }
}


void DisplayMap(vector<vector<vector<int>>> &map,Camera camera){
    for(float x=0; x<3; x++){
        for(float y=0; y<3; y++){
            for(float z=0; z<3; z++){
                DrawCubeWires(Vector3 {x,y,z}, 1.0f, 1.0f, 1.0f, BLACK);
                if(map[x][y][z] == 1){
                    unsigned char d = (sqrt(pow(2,camera.position.x - x)+pow(2,camera.position.y - y)+pow(2,camera.position.z - z)))*4;
                    unsigned char r=230-d, g=41-d, b=55-d;
                    DrawCube(Vector3 {x,y,z}, 0.5f, 0.5f, 0.5f, (Color){r,g,b,255});
                }
                else if(map[x][y][z] == -1){
                    unsigned char d = (sqrt(pow(2,camera.position.x - x)+pow(2,camera.position.y - y)+pow(2,camera.position.z - z)))*4;
                    unsigned char r=0,g=121-d,b=241-d;
                    DrawCube(Vector3 {x,y,z}, 0.5f, 0.5f, 0.5f, (Color){r,g,b,255});
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
        else{up.at((0-temp1)-1) = -1;}
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

void PlayerInput(vector<vector<vector<int>>> &map, Camera &camera, int &player){
    if(IsKeyPressed(KEY_UP)){          //Movement of the camera (Map)
            UpdateRelative(1,0,camera);
            SetPos(camera);
        }else if(IsKeyPressed(KEY_DOWN)){
            UpdateRelative(1,1,camera);
            SetPos(camera);
        }else if(IsKeyPressed(KEY_RIGHT)){
            UpdateRelative(2,1,camera);
            SetPos(camera);
        }else if(IsKeyPressed(KEY_LEFT)){
            UpdateRelative(2,0,camera);
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
        }else if((IsKeyPressed(KEY_SPACE))&&(map[rectpos.x][rectpos.y][rectpos.z] == 0)){
            map[rectpos.x][rectpos.y][rectpos.z] = player;
            player = -player;
        }
}

int main(void){
    float Clock;
    bool blink = true;
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
        Clock += GetFrameTime();
        int gamestate = GameState(map);
        UpdateCamera(&camera,0);
        if(gamestate == 0){PlayerInput(map, camera, player);}
        if( Clock > 1.5){blink = false; Clock = 0;}else{blink = true;} 
        BeginDrawing();

            ClearBackground(RAYWHITE);
            if((gamestate == 1)||(gamestate == -1)){
                    DrawRectangle(0, 0, screenWidth, screenHeight, (Color){0,0,0,80});
                    DrawText("PRESS ENTER TO  TRY AGAIN", 100, 300, 40.0f, BLACK);
                    if(gamestate == 1){
                         DrawText("RED WON", 280, 70, 40.0f, BLACK);
                    }else if(gamestate == -1 ){
                         DrawText("BLUE WON", 280, 70, 40.0f, BLACK);
                    }else if(gamestate == 0){
                         DrawText("THE GAME WAS A DRAW", 260, 70, 40.0f, BLACK);
                    }
                    if(IsKeyPressed(KEY_ENTER)){ 
                        vector<vector<vector<int>>> temp(3,vector<vector<int>>(3,vector<int>(3,0)));
                        map = temp;
                     }
            }

            BeginMode3D(camera); // Start 3D mode

                    DisplayMap(map,camera);
                    if((gamestate == 0 )&& (blink == true)){DrawCube(rectpos, 0.5f, 0.5f, 0.5f, BLACK);}

            EndMode3D(); // End 3D mode
            DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", camera.position.x, camera.position.y, camera.position.z), 610, 60, 10, BLACK);
            DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", camera.target.x, camera.target.y, camera.target.z), 610, 30, 10, BLACK);
            DrawText("Press ESC to close", 10, 10, 20, BLACK);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}