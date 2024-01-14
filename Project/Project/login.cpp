#include "Header.h"
bool login()
{
    while (!WindowShouldClose()) {
        BeginDrawing();
        Color backgroundColor = { 225, 225, 225, 90};
        ClearBackground(backgroundColor);
        DrawText("Email:", 15, loginHeight / 2 - 125, 20, BLACK);
        DrawRectangle(15, loginHeight / 2 - 100, 200, 30, WHITE);
        DrawText("Password:", loginWidth / 2 - 100, loginHeight / 2 - 50, 20, DARKGRAY);
        DrawRectangle(loginWidth / 2 - 100, loginHeight / 2 - 25, 200, 30, DARKGRAY);

        EndDrawing();
    }
    return false;
}