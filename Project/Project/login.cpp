#include "Header.h"
bool login()
{
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(LIGHTGRAY);
        DrawText("Email", loginWidth / 2 - 100, loginHeight / 2 - 125, 20, DARKGRAY);
        DrawRectangle(loginWidth / 2 - 100, loginHeight / 2 - 100, 200, 30, DARKGRAY);
        DrawText("Password", loginWidth / 2 - 100, loginHeight / 2 - 50, 20, DARKGRAY);
        DrawRectangle(loginWidth / 2 - 100, loginHeight / 2 - 25, 200, 30, DARKGRAY);

        DrawRectangle(loginWidth / 2 - 100, loginHeight / 2 + 25, 90, 40, DARKGRAY);
        DrawRectangle(loginWidth / 2 - 100 + 110, loginHeight / 2 + 25, 90, 40, DARKGRAY);

        DrawText("Login", loginWidth / 2 - 80, loginHeight / 2 + 35, 20, WHITE);
        DrawText("Sign up", loginWidth / 2 + 20, loginHeight / 2 + 35, 20, WHITE);

        EndDrawing();
    }
    return false;
}