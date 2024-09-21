#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <raylib.h>

typedef struct{

    int originX, originY;
    int width, height;
    int cellW, cellH;
    int rows, cols;
    
    Rectangle* cells;

}Grid; /*grid structure*/

void init_grid(Grid* g) {
    g->cells = malloc(sizeof(Rectangle) * g->rows * g->cols);
    int nextX, nextY;
    
    for (int i = 0; i < g->rows; i++) {
        nextX = g->originX;
        nextY = g->originY + i * g->cellH;
        
        for (int j = 0; j < g->cols; j++) {
            g->cells[i * g->cols + j] = (Rectangle){nextX, nextY, g->cellW, g->cellH};
            nextX += g->cellW;
        }
    }
}

int main(int argc, char* argv[]){

    /*window and grid parameters*/
    const int width = 800, height = 800;

    Grid environment = {0, 0, width, height, width / 8, height / 8, 8, 8, NULL};
    
    if (argc > 1) {
        environment.rows = atoi(argv[1]);
        environment.cols = (argc > 2) ? atoi(argv[2]) : environment.cols;
        environment.cellW = environment.width / environment.cols;
        environment.cellH = environment.height / environment.rows;
    }

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, "Grid");
    SetTargetFPS(60);

    init_grid(&environment);

    /*main loop*/
    while(!WindowShouldClose()){

        /*if the window is not minimized draw the grid, otherwise do nothing*/
        if(!IsWindowMinimized()){
            BeginDrawing();
            ClearBackground(WHITE);
            
            for(int i = 0; i<environment.width*environment.height; i++){
                DrawRectangleLines(environment.cells[i].x, environment.cells[i].y, 
                    environment.cells[i].width, environment.cells[i].height, BLACK);
            }

            EndDrawing();
        }
    }

    //free resources for grid
    free(environment.cells);

    CloseWindow();

    return 0;
}
