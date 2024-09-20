#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <raylib.h>

Rectangle* init_grid( const int gridWidth, const int gridHeight, const int rectW, const int rectH){

    Rectangle* grid = malloc(sizeof(Rectangle)*gridWidth*gridHeight);
    Rectangle tmp;

    int nextX = 0, nextY = 0;

    for(int i = 0; i<gridWidth; i++){
        nextX = 0;
        for(int j = 0; j<gridHeight; j++){
            tmp.x = nextX;
            tmp.y = nextY;
            tmp.width = rectW;
            tmp.height = rectH;

            grid[i * gridWidth + j] = tmp;

            nextX += rectW;
        }
        nextY += rectH;
    }

    return grid;
}

int main(int argc, char* argv[]){

    /*window and grid parameters*/
    const int width = 800, height = 600;
    int gridWidth = 8, gridHeight = 8;

    /*initialize the window and set it as resizable*/
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, "Test");
    
    /*get grid dimensions from arguments (if provided)*/
    if(argc>1){
        gridWidth = atoi(argv[1]);
        if(argc>2){
            gridHeight = atoi(argv[2]);
        }
    }

    /*set rectangle dimensions based on window size and grid dimensions, grid must fill all the window*/
    const int rectW = width/gridWidth; 
    const int rectH = height/gridHeight;

    Rectangle* grid = NULL;
    
    /*fill the grid with rectangles*/
    grid = init_grid(gridWidth, gridHeight, rectW, rectH);

    /*main loop*/
    while(!WindowShouldClose()){

        /*if the window is not minimized draw the grid, otherwise do nothing*/
        if(!IsWindowMinimized()){
            BeginDrawing();
            ClearBackground(WHITE);
            
            for(int i = 0; i<gridWidth*gridHeight; i++){
                DrawRectangleLines(grid[i].x, grid[i].y, grid[i].width, grid[i].height, BLACK);
            }

            EndDrawing();
        }
        else{
            sleep(1);
        }
    }

    //free resources for grid
    free(grid);

    return 0;
}
