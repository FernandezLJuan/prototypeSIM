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

void init_grid(const char* path, Grid* g){
    /*reads configuration file and sets grid parameters*/

    FILE* config = fopen(path, "r");

    config_t cfg;
    config_setting_t *settings;

    config_init(&cfg);
    if(config_read(&cfg, config) == CONFIG_FALSE){
        /*log the parsing error to the screen*/
        printf("ERROR PARSING COFIGURATION FILE.\n");
        printf("Error on line %d, on file %s: \n%s\n", config_error_line(&cfg), config_error_file(&cfg), config_error_text(&cfg));
    }
    else{
        /*change grid settings based on file*/
        config_lookup_int(&cfg, "application.environment.cellDims.width", &(g->cellW));
        config_lookup_int(&cfg, "application.environment.cellDims.height", &(g->cellH));
        config_lookup_int(&cfg, "application.environment.pos.x",&(g->originX));
        config_lookup_int(&cfg, "application.environment.pos.y", &(g->originY));
        config_lookup_int(&cfg, "application.environment.rows",&(g->rows));
        config_lookup_int(&cfg, "application.environment.cols",&(g->cols));

        g->width = g->cols * g->cellW;
        g->height = g->rows * g->cellH;
    }

}

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

    char* filename = "default.cfg";

    if(argc>1){
        filename = argv[1];
    }
    else{
        printf("Using default settings.\nCustom settings file can be provided when launching the program\n");
    }

    /*window parameters*/
    const int width = 800, height = 800;

    /*init window*/
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTraceLogLevel(LOG_NONE);
    InitWindow(width, height, "Grid");
    SetTargetFPS(60);

    /*create and fill grid*/
    Grid environment;
    init_grid(filename, &environment);
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
