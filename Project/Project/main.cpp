#include "Header.h"
void main()
{

    InitWindow(screenWidth, screenHeight, "Program");


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);
        EndDrawing();
    }
    CloseWindow();
}