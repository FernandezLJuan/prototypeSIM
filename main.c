#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

int main(int argc, char* argv[]){

    int gridWidth = 8, gridHeight = 8;
    const int rectW = 20, rectH = 20;

    if(argc>1){
        gridWidth = atoi(argv[1]);
        if(argc>2){
            gridHeight = atoi(argv[2]);
        }
    }

    const int width = 800, height = 600;

    Rectangle* grid = malloc(sizeof(Rectangle)*gridWidth*gridHeight);
    Rectangle tmp;

    int nextX = 50, nextY = 50;

    for(int i = 0; i<gridWidth; i++){

        nextX = 50;
        for(int j = 0; j<gridHeight; j++){
            tmp.x = nextX + rectW;
            tmp.y = nextY;
            tmp.width = rectW;
            tmp.height = rectH;

            grid[i * gridWidth + j] = tmp;

            nextX += rectW;
        }
        
        nextY += rectH;
    }

    InitWindow(width, height, "Test");

    while(!WindowShouldClose()){
        if(!IsWindowMinimized()){
            BeginDrawing();
            
            for(int i = 0; i<gridWidth*gridHeight; i++){
                DrawRectangleLines(grid[i].x, grid[i].y, grid[i].width, grid[i].height, BLACK);
            }

            ClearBackground(WHITE);
            EndDrawing();
        }
    }

    free(grid);

    return 0;
}
