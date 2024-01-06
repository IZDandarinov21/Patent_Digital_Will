#include "Header.h"
#include <stdlib.h>
#include <time.h>

struct TRASH {
    int posX = 0;
    int posY = 0;
    bool grabbed = true;
};

short inGame(float charSpeed, int gameTimeHolder, short map, const short trash)
{
    //const short trash = 10;
    TRASH objects[20];
    
    short trashCounter = 0;
    int trashPicked = 0;
    int frameTime = 0;
    int randPosX = 0;
    int randPosY = 0;
    int gameTime = gameTimeHolder * GetFrameTime(); // Game time in seconds, multiplied by the frametime to convert to frames
    int score = 0;
    bool gameOver = false;
    Texture2D map1 = LoadTexture("../assets/map_1.png");
    Texture2D map2 = LoadTexture("../assets/map_2.png");

    Texture2D charFront = LoadTexture("../assets/charFront.png");
    Texture2D charBack = LoadTexture("../assets/charBack.png");
    Texture2D charLeft = LoadTexture("../assets/charLeft.png");
    Texture2D charRight = LoadTexture("../assets/charRight.png");

    Texture2D trashSprite = LoadTexture("../assets/trash.png");
    Texture2D dumpsterSprite = LoadTexture("../assets/dumpster.png");
    Font font = LoadFontEx("../assets/PixAntiqua.ttf", 32, 0, 250);

    Vector2 spritePosition = { static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2) };
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (!gameOver) gameTime--;
        frameTime++;
        //Color bgColor = { 0, 51, 102 };
        BeginDrawing();
        ClearBackground(BLACK);
        if(map == 1) DrawTexturePro(map1, { 0.0f, 0.0f, (float)map1.width, (float)map1.height }, { 0.0f, 0.0f, (float)GetScreenWidth() - 350, (float)GetScreenHeight() }, { 0, 0 }, 0.0f, WHITE);
        else if(map == 2) DrawTexturePro(map2, { 0.0f, 0.0f, (float)map2.width, (float)map2.height }, { 0.0f, 0.0f, (float)GetScreenWidth() - 350, (float)GetScreenHeight() }, { 0, 0 }, 0.0f, WHITE);
        for (int i = 0; i < trash; i++)
        {
            if (objects[i].grabbed == false)
            {
                DrawTexture(trashSprite, objects[i].posX, objects[i].posY, WHITE);
            }
        }
        DrawTexture(dumpsterSprite, screenWidth / 2 - 64, screenHeight - 125, WHITE);
        
        //DrawTextEx(font, TextFormat("Current randPos: %d, %d", randPosX, randPosY), { screenWidth / 2 - 200, 100 }, font.baseSize, 2.0f, WHITE);
        DrawTextEx(font, TextFormat("Trash picked: %d", trashPicked), { screenWidth - 300, screenHeight - 40 }, font.baseSize, 2.0f, WHITE);
        DrawTextEx(font, TextFormat("Score: %d", score), { screenWidth - 250, screenHeight / 2 }, font.baseSize, 2.0f, WHITE);
        DrawTextEx(font, TextFormat("Time remaining: %d", gameTime / 60), { screenWidth - 315, 20 }, 30, 2.0f, WHITE); // Display the remaining time
        if (!gameOver)
        {
            if (IsKeyDown(KEY_W) && spritePosition.y > 0) { spritePosition.y -= charSpeed; DrawTexture(charBack, static_cast<int>(spritePosition.x), static_cast<int>(spritePosition.y), WHITE);
            }
            if (IsKeyDown(KEY_S) && spritePosition.y < screenHeight - 125 - charFront.height) { spritePosition.y += charSpeed; DrawTexture(charFront, static_cast<int>(spritePosition.x), static_cast<int>(spritePosition.y), WHITE);
            }
            if (IsKeyDown(KEY_A) && spritePosition.x > 0) { spritePosition.x -= charSpeed; DrawTexture(charLeft, static_cast<int>(spritePosition.x), static_cast<int>(spritePosition.y), WHITE);
            }
            if (IsKeyDown(KEY_D) && spritePosition.x < screenWidth - 325 - charRight.width) { spritePosition.x += charSpeed; DrawTexture(charRight, static_cast<int>(spritePosition.x), static_cast<int>(spritePosition.y), WHITE);
            }
            if (!(  IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D)) || !(spritePosition.y < screenHeight - 125 - charFront.height) || !(spritePosition.x < screenWidth - 325 - charRight.width)) { DrawTexture(charFront, static_cast<int>(spritePosition.x), static_cast<int>(spritePosition.y), WHITE); }
        }
        

        if (frameTime >= 60)
        {
            randPosX = rand() % 850 + 100;
            randPosY = rand() % 500 + 200;
            frameTime = 0;
            if (!gameOver)
            {
                for (int i = 0; i < trash; i++)
                {
                    if (objects[i].grabbed == true)
                    {
                        objects[i].grabbed = false;
                        objects[i].posX = randPosX;
                        objects[i].posY = randPosY;
                        break;
                    }
                }
            }
            
        }

        for (int i = 0; i < trash; i++)
        {
            if (objects[i].grabbed == false)
            {
                // Check for collision with sprite
                if (CheckCollisionRecs({ (float)spritePosition.x, (float)spritePosition.y, (float)charFront.width, (float)charFront.height }, { (float)objects[i].posX - 15, (float)objects[i].posY - 15, 30, 30 }))
                {
                    //DrawTextEx(font, "[SPACE] to pick up", { spritePosition.x + 20, spritePosition.y - 20 }, font.baseSize, 2.0f, WHITE);
                    if (IsKeyPressed(KEY_SPACE) && trashCounter < 3)
                    {
                        trashCounter++;
                        objects[i].grabbed = true;
                        trashPicked++;
                        gameTime += 1 * 60; // Add 2 seconds to the game time
                        score += 10;
                    }

                }
                DrawTexture(trashSprite, objects[i].posX, objects[i].posY, WHITE);
            }
        }


        if (CheckCollisionRecs({ (float)spritePosition.x, (float)spritePosition.y, (float)charFront.width, (float)charFront.height }, { screenWidth / 2 - 32, screenHeight - 125 - 15, 60, 30 }))
        {
            if(trashCounter == 1) score += 10;
            if(trashCounter == 2) score += 20;
            if(trashCounter == 3) score += 30;
            trashPicked = 0;
            trashCounter = 0;
        }


        if (gameTime <= 0) {
            gameOver = true;
            DrawTextEx(font, "GAME OVER", { screenWidth / 2 - MeasureText("GAME OVER", 50) / 2 + 15, screenHeight / 2 - 100 }, 50, 2.0f, RED);
            DrawTextEx(font, TextFormat("High Score: %d", score), { screenWidth / 2 - MeasureText(TextFormat("High Score: %d", score), 30) / 2, screenHeight / 2 - 50 }, 30, 2.0f, RED);
            DrawTextEx(font, "Press [ENTER] to start again", { screenWidth / 2 - MeasureText("Press [ENTER] to start again", 20) / 2 + 5, screenHeight / 2 + 100 }, 20, 2.0f, WHITE);
            DrawTextEx(font, "Press [ESC] to return to menu", { screenWidth / 2 - MeasureText("Press [ESC] to return to menu", 20) / 2 + 5, screenHeight / 2 + 140 }, 20, 2.0f, WHITE);
            if (IsKeyPressed(KEY_ENTER)) {
                gameTime = gameTimeHolder * 60;
                trashPicked = 0;
                gameOver = false;
                for (int i = 0; i < trash; i++) {
                    objects[i].grabbed = true;
                }
            }
        }

        EndDrawing();
    }

    UnloadTexture(map1);
    UnloadTexture(map2);
    UnloadTexture(charFront);
    UnloadTexture(charBack);
    UnloadTexture(charRight);
    UnloadTexture(charLeft);

    UnloadTexture(trashSprite);
    UnloadTexture(dumpsterSprite);
    UnloadFont(font);
    return 0;
}
