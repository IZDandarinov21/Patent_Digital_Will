#include "Header.h"
void app()
{
    InitWindow(screenWidth, screenHeight, "PATENT Bank");

    Font font = LoadFontEx("../assets/PixAntiqua.ttf", 32, 0, 250);


    // start displaying
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        //DrawLine(0, 100, screenWidth, 100, BLACK);
        DrawRectangle(0, 100, 1300, 5, BLACK);
        EndDrawing();
    }


    CloseWindow();
}