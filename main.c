#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

int main(int argc, char* argv[]){

    const int width = 800, height = 600;

    InitWindow(width, height, "Test");

    while(!WindowShouldClose()){
        if(!IsWindowMinimized()){
            BeginDrawing();
            DrawRectangle(100,100,20,20,BLACK);
            ClearBackground(WHITE);
            EndDrawing();
        }
    }

    return 0;
}
