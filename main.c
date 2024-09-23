#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libconfig.h>
#include <raylib.h>

typedef enum {CELL_FREE, CELL_OBSTACLE, CELL_ROBOT, CELL_GOAL} cellType;

typedef struct{
    int id;
    cellType type;

    Rectangle cellRect;

}Cell;

typedef struct{

    int originX, originY;
    int width, height;
    int cellW, cellH;
    int rows, cols;
    
    Cell* cells; /*array of cells on a grid*/

}Grid; /*grid structure*/

void fill_grid(Grid* g) {
    g->cells = malloc(sizeof(Cell) * g->rows * g->cols);
    int nextX, nextY;
    double obsProb = 0.2;
    double isObstacle = 0.0;

    for (int i = 0; i < g->rows; i++) {
        nextX = g->originX;
        nextY = g->originY + i * g->cellH;
        
        for (int j = 0; j < g->cols; j++) {
            isObstacle = (rand() % 10001) / 10000.0;

            g->cells[i * g->cols + j].cellRect = (Rectangle){nextX, nextY, g->cellW, g->cellH};

            if(isObstacle<obsProb){
                g->cells[i * g->cols + j].type = CELL_OBSTACLE;
            }
            else{
                g->cells[i * g->cols + j].type = CELL_FREE;
            }
            nextX += g->cellW;
        }
    }
}

void render_grid(Grid* g){
    
    Cell currentCell;

    for(int i = 0; i<g->rows; i++){
        for(int j = 0; j<g->cols; j++){
            currentCell = g->cells[i * g->cols + j];
            if(currentCell.type == CELL_FREE){
                DrawRectangleLines(currentCell.cellRect.x, currentCell.cellRect.y, currentCell.cellRect.width, currentCell.cellRect.height, BLACK);
            }
            else if(currentCell.type == CELL_OBSTACLE){
                DrawRectangle(currentCell.cellRect.x, currentCell.cellRect.y, currentCell.cellRect.width, currentCell.cellRect.height, GRAY);
            }
        }
    }

}

int main(int argc, char* argv[]){

    /*window and grid parameters*/
    const int width = 800, height = 800;

    Grid environment = {20, 20, width / 2, height / 2, width / 8, height / 8, 8, 8, NULL};
    
    printf("%d, %d\n", environment.width, environment.height);

    if (argc > 1) {
        environment.rows = atoi(argv[1]);
        environment.cols = (argc > 2) ? atoi(argv[2]) : environment.cols;
    }
    else{
        printf("rows = %d, cols = %d\nYou can specify this values when launching the code\n", environment.rows, environment.cols);
    }

    environment.cellW = environment.width / environment.cols;
    environment.cellH = environment.height / environment.rows;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTraceLogLevel(LOG_NONE);
    InitWindow(width, height, "Grid");
    SetTargetFPS(60);

    fill_grid(&environment);

    /*main loop*/
    while(!WindowShouldClose()){

        /*if the window is not minimized draw the grid, otherwise do nothing*/
        if(!IsWindowMinimized()){
            BeginDrawing();
            ClearBackground(WHITE);
            
            render_grid(&environment);

            EndDrawing();
        }
    }

    //free resources for grid
    free(environment.cells);

    CloseWindow();

    return 0;
}
