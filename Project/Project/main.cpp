#include "Header.h"
void main()
{
    InitWindow(screenWidth, screenHeight, "Banking app");
    Font font = LoadFontEx("../assets/PixAntiqua.ttf", 32, 0, 250);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextEx(font, "[SPACE] Toggle Fullscreen", { screenWidth / 2 - MeasureText("[SPACE] Toggle Fullscreen", 20), screenHeight / 2 - 100}, 50, 2.0f, WHITE);
        if (IsKeyPressed(KEY_SPACE))
        {
            ToggleFullscreen();
        }
        EndDrawing();
    }
    CloseWindow();
}