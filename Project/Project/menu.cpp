#include "Header.h"
short currentScreen;
// 0 - MAIN MENU
// 1 - SETTINGS
// 2 - PREGAME SCREEN
// 3 - INGAME SCREEN
// 4 - END SCREEN


void main()
{

    InitWindow(screenWidth, screenHeight, "raylib menu example");

    Texture2D background = LoadTexture("../assets/menu_background.png");
    Texture2D logo = LoadTexture("../assets/logo_menu.png");
    Texture2D settings = LoadTexture("../assets/settings_menu.png");
    Texture2D settings_icon = LoadTexture("../assets/settings_icon.png");
    Texture2D mapSelect_1 = LoadTexture("../assets/mapSmall_1.png");
    Texture2D mapSelect_2 = LoadTexture("../assets/mapSmall_2.png");

    //Texture2D settings_icon_pressed = LoadTexture("../assets/settings_icon_pressed.png");
    SetTargetFPS(60);
    short frameTime = 0;

    currentScreen = 0;

    Vector2 playButtonPosition = { (float)screenWidth / 2 - 190, (float)screenHeight / 2 + 150 };
    Vector2 exitButtonPosition = { 25, (float)screenHeight - 75 };
    Vector2 changeMenuButton = { (float)screenWidth / 2 - 200, (float)screenHeight / 2 + 50 };
    Vector2 settingsButtonPosition = { screenWidth - 150, 0 };


    Vector2 mapSelectPosition = { screenWidth / 2 - 135, screenHeight / 2 - 150 };




    Font font = LoadFontEx("../assets/PixAntiqua.ttf", 32, 0, 250);

    bool showPreGameScreen = true;
    bool useTtf = false;
    bool closeGame = false;
    bool spaceBarShow = true;
    short numberOfObjects = 10;
    float charSpeed = 6.0f;
    short currentMap = 1;
    int gameTime = 30;

    while (true)
    {
        frameTime++;

        if (WindowShouldClose() && currentScreen == 0 && closeGame == false)
            closeGame = true;
        else if (closeGame && IsKeyPressed(KEY_ESCAPE))
        {
            break;
        }
        switch (currentScreen)
        {
        case 0: case 1:
        {
            BeginDrawing();
            ClearBackground(BLACK);

            DrawTexture(background, 0, 0, WHITE);
            DrawTexture(logo, screenWidth / 2 - 222.5, 100, WHITE);
            if (closeGame)
            {
                DrawTextEx(font, "Press ESC again if you want to quit", { 475, 425 }, font.baseSize, 2.0f, RED);
            }
            if (CheckCollisionPointRec(GetMousePosition(), { settingsButtonPosition.x, settingsButtonPosition.y, 190, 135 }))
            {
                DrawTexture(settings_icon, settingsButtonPosition.x, settingsButtonPosition.y, GOLD);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    if (currentScreen == 0)
                    {
                        currentScreen = 1;
                    }
                    else if (currentScreen == 1)
                    {
                        currentScreen = 0;
                    }
                }
            }
            else
            {
                DrawTexture(settings_icon, settingsButtonPosition.x, settingsButtonPosition.y, WHITE);
            }




            if (spaceBarShow)
                DrawTextEx(font, "Press SPACE to start", { playButtonPosition.x, playButtonPosition.y }, 40, 2.0f, WHITE);

            if (IsKeyPressed(KEY_SPACE))
            {
                if (showPreGameScreen)
                    currentScreen = 2;
                else
                    currentScreen = 3;



            }


            if (CheckCollisionPointRec(GetMousePosition(), { exitButtonPosition.x, exitButtonPosition.y, 100, 50 }))
            {
                DrawTextEx(font, "Exit", { exitButtonPosition.x + 18, exitButtonPosition.y + 15 }, 40, 2.0f, RED);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    CloseWindow();
                }
            }
            else
            {
                DrawTextEx(font, "Exit", { exitButtonPosition.x + 18, exitButtonPosition.y + 15 }, 40, 2.0f, WHITE);
            }

            if (currentScreen == 1)
            {

                DrawTexture(settings, screenWidth / 2 - 260, screenHeight / 2 - 375, WHITE);

                DrawTextEx(font, "Settings", { screenWidth / 2 - 110, 100 }, 60, 2.0f, WHITE);
                DrawTextEx(font, "Select map:", { mapSelectPosition.x + 40, mapSelectPosition.y - 75 }, 40, 2.0f, WHITE);


                if (CheckCollisionPointRec(GetMousePosition(), { mapSelectPosition.x - 100, mapSelectPosition.y + 80, 60, 60 }))
                {
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        if (currentMap == 1)
                            currentMap = 1;
                        else
                            currentMap--;
                    }
                    DrawTextEx(font, "<", { mapSelectPosition.x - 85, mapSelectPosition.y + 70 }, 100, 2.0f, GOLD);

                }
                else { DrawTextEx(font, "<", { mapSelectPosition.x - 85, mapSelectPosition.y + 70 }, 100, 2.0f, WHITE); }

                if (CheckCollisionPointRec(GetMousePosition(), { mapSelectPosition.x + 340, mapSelectPosition.y + 80, 60, 60 }))
                {
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        if (currentMap == 1)
                            currentMap = 1;
                        else
                            currentMap++;
                    }
                    DrawTextEx(font, ">", { mapSelectPosition.x + 355, mapSelectPosition.y + 70 }, 100, 2.0f, GOLD);
                }
                else { DrawTextEx(font, ">", { mapSelectPosition.x + 355, mapSelectPosition.y + 70 }, 100, 2.0f, WHITE); }

                if(currentMap == 1) DrawTexture(mapSelect_1, mapSelectPosition.x, mapSelectPosition.y, WHITE);
                else if (currentMap == 2) DrawTexture(mapSelect_2, mapSelectPosition.x, mapSelectPosition.y, WHITE);

                if(numberOfObjects < 10) DrawTextEx(font, TextFormat(" Number of objects:     %d     ", numberOfObjects), { screenWidth / 2 - 195, 600 }, 30, 2.0f, WHITE);
                else DrawTextEx(font, TextFormat(" Number of objects:     %d     ", numberOfObjects), { screenWidth / 2 - 200, 600 }, 30, 2.0f, WHITE);
                if (CheckCollisionPointRec(GetMousePosition(), { screenWidth / 2 + 200, 595, 30, 30 }))
                {
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        if (numberOfObjects < 20) numberOfObjects++;
                        else numberOfObjects = 1;
                    }
                    DrawTextEx(font, "+", { screenWidth / 2 + 200, 595 }, 40, 2.0f, GREEN);
                }
                else
                    DrawTextEx(font, "+", { screenWidth / 2 + 200, 595 }, 40, 2.0f, WHITE);
                if (CheckCollisionPointRec(GetMousePosition(), { screenWidth / 2 + 115, 595, 30, 30 }))
                {
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        if (numberOfObjects > 1) numberOfObjects--;
                        else numberOfObjects = 20;
                    }
                    DrawTextEx(font, "-", { screenWidth / 2 + 115, 595 }, 40, 2.0f, RED);
                }
                else
                    DrawTextEx(font, "-", { screenWidth / 2 + 115, 595 }, 40, 2.0f, WHITE);


                DrawTextEx(font, TextFormat("Character speed:     %.0f    ", charSpeed), { (float)screenWidth / 2 - 192, 640 }, 30, 2.0f, WHITE);
                if (CheckCollisionPointRec(GetMousePosition(), { screenWidth / 2 + (float)157.5, 632.5, 30, 30 }))
                {
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        if (charSpeed < 50) charSpeed++;
                    }
                    DrawTextEx(font, ">", { screenWidth / 2 + (float)157.5, 632.5 }, 40, 2.0f, GREEN);
                }
                else
                    DrawTextEx(font, ">", { screenWidth / 2 + (float)157.5, 632.5 }, 40, 2.0f, WHITE);
                if (CheckCollisionPointRec(GetMousePosition(), { screenWidth / 2 + 90, 632.5, 30, 30 }))
                {
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        if (charSpeed > 1) charSpeed--;
                    }
                    DrawTextEx(font, "<", { screenWidth / 2 + 90, 632.5 }, 40, 2.0f, RED);
                }
                else
                    DrawTextEx(font, "<", { screenWidth / 2 + 90, 632.5 }, 40, 2.0f, WHITE);

                DrawTextEx(font, TextFormat("Game time:     %d    ", gameTime), { (float)screenWidth / 2 - 192, 680 }, 30, 2.0f, WHITE);
                if (CheckCollisionPointRec(GetMousePosition(), { screenWidth / 2 + (float)75, 672.5, 30, 30 }))
                {
                    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                    {
                        if (gameTime < 301) gameTime++;
                        else gameTime = 1;
                    }
                    DrawTextEx(font, ">", { screenWidth / 2 + (float)75, 672.5 }, 40, 2.0f, GREEN);
                }
                else
                    DrawTextEx(font, ">", { screenWidth / 2 + (float)75, 672.5 }, 40, 2.0f, WHITE);
                if (CheckCollisionPointRec(GetMousePosition(), { screenWidth / 2 - 10, 672.5, 30, 30 }))
                {
                    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                    {
                        if (gameTime > 1) gameTime--;
                        else gameTime = 300;
                    }
                    DrawTextEx(font, "<", { screenWidth / 2 - 10, 672.5 }, 40, 2.0f, RED);
                }
                else
                    DrawTextEx(font, "<", { screenWidth / 2 - 10, 672.5 }, 40, 2.0f, WHITE);

               
                if (CheckCollisionPointRec(GetMousePosition(), { (float)screenWidth / 2 - 192, 720 , 275, 30 }))
                {
                    DrawTextEx(font, TextFormat("Toggle fullscreen"), { (float)screenWidth / 2 - 192, 720 }, 30, 2.0f, GOLD);
                    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                    {
                        ToggleFullscreen();
                    }
                }
                else DrawTextEx(font, TextFormat("Toggle fullscreen"), { (float)screenWidth / 2 - 192, 720 }, 30, 2.0f, WHITE);

                if (IsKeyPressed(KEY_ESCAPE)) currentScreen = 0;

            }


            EndDrawing();
            break;
        }
        case 2:
        {

            currentScreen = preGame();
            break;
        }
        case 3:
        {
            currentScreen = inGame(charSpeed, gameTime, currentMap, numberOfObjects);
        }
        }
        if (frameTime >= 60)
        {
            if (spaceBarShow)
                spaceBarShow = 0;
            else
                spaceBarShow = 1;

            frameTime = 0;
        }
    }
    UnloadTexture(background);
    UnloadTexture(logo);
    UnloadTexture(settings);
    UnloadTexture(settings_icon);
    UnloadFont(font);
    UnloadTexture(mapSelect_1);
    UnloadTexture(mapSelect_2);
    CloseWindow();
}