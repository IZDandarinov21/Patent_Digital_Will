#include "Header.h"
short preGame()
{
	Texture2D WASD = LoadTexture("../assets/WASD.png");
	Font font = LoadFontEx("../assets/PixAntiqua.ttf", 32, 0, 250);

	while (!(IsKeyPressed(KEY_ENTER)) && !WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTextEx(font, "Press ENTER to start", { screenWidth / 2 - MeasureText("Press ENTER to start", font.baseSize) / 2 + 15, screenHeight / 2 + 300 }, font.baseSize, 2.0f, WHITE);
		DrawTextEx(font, "Press ESC to go back to menu", { screenWidth / 2 - MeasureText("Press ESC to go back to menu", font.baseSize) / 2 + 15, screenHeight / 2 + 340 }, font.baseSize, 2.0f, WHITE);
		DrawTextEx(font, "Press Space to interact", { screenWidth / 2 - MeasureText("Press Space to interact", font.baseSize) / 2 + 10, screenHeight / 2 + 100 }, font.baseSize, 2.0f, WHITE); // Added this line
		DrawTextEx(font, "Controls", { screenWidth / 2 - MeasureText("Controls", font.baseSize) / 2, screenHeight / 2 - 300 }, font.baseSize, 2.0f, WHITE);
		DrawTexture(WASD, screenWidth / 2 - WASD.width / 2, screenHeight / 2 - WASD.height / 2, WHITE);
		EndDrawing();
	}
	UnloadTexture(WASD);
	UnloadFont(font);
	if (IsKeyPressed(KEY_ENTER)) return 3;
	return 0;
}