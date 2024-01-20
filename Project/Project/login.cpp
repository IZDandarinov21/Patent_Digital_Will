#include "Header.h"
#define MAX_INPUT_CHARS 24
Rectangle emailInputBox = { 15, loginHeight / 2 - 100, 275, 30 };
Rectangle passwordInputBox = { 15, loginHeight / 2 - 25, 275, 30 };
bool isTypingGlobal[2] = { 0 , 0 };
int framesCounter = 0;
int backspaceCounter = 0;
int backspaceHoldDown = 0;
int charCountGlobal[2] = { 0 , 0 };

struct LOGIN_INFO 
{
    string email;
    string password;
};

string convertToString(char* arr)
{
    string str = arr;
    return str;
}

bool getInput(Rectangle inputBox, bool isTyping, char inputArr[], int charCount)
{

    if (CheckCollisionPointRec(GetMousePosition(), inputBox))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && isTyping == 0)
        {
            isTyping = 1;
        }
    }

    else if (isTyping == 1 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        isTyping = 0;
    }

    if (CheckCollisionPointRec(GetMousePosition(), inputBox)) SetMouseCursor(MOUSE_CURSOR_IBEAM);
    if (isTyping == 1)
    {

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();

        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (charCount < MAX_INPUT_CHARS))
            {
                inputArr[charCount] = (char)key;
                inputArr[charCount + 1] = '\0'; // Add null terminator at the end of the string.
                charCount++;
            }

            key = GetCharPressed();  // Check next character in the queue
        }
        if (IsKeyDown(KEY_BACKSPACE))
        {
            if (backspaceCounter > 30)
            {
                backspaceHoldDown++;
                if (backspaceHoldDown > 3)
                {
                    charCount--;
                    if (charCount < 0) charCount = 0;
                    inputArr[charCount] = '\0';
                    backspaceHoldDown = 0;
                }

            }
            backspaceCounter++;
        }


        if (IsKeyPressed(KEY_BACKSPACE))
        {
            charCount--;
            if (charCount < 0) charCount = 0;
            inputArr[charCount] = '\0';
        }
    }
  
    if (isTyping == 1) framesCounter++;
    
    if (isTypingGlobal[0] == 1) {
        charCountGlobal[0] = charCount;
    }
    if (isTypingGlobal[1] == 1) {
        charCountGlobal[1] = charCount;
    }
    return isTyping;
}

bool login()
{
    InitWindow(loginWidth, loginHeight, "PATENT BANK | PLEASE LOG IN . . .");
    Texture2D logo = LoadTexture("../assets/logo.png");

    Font customFont = LoadFont("../assets/lato.ttf");

    // Sample login info

    LOGIN_INFO accounts[10];
    accounts[0].email = "john@gmail.com";
    accounts[0].password = "123456";

    // EMAIL INPUT BOX
    char emailInput[MAX_INPUT_CHARS + 1] = "\0";
    int emailCharCount = 0;

    // LOGIN INPUT BOX
    char passwordInput[MAX_INPUT_CHARS + 1] = "\0";
    char passwordInputHidden[MAX_INPUT_CHARS + 1] = "\0";
    int passwordCharCount = 0;
    int backspaceHoldDown = 0;
    



   
    DrawTexture(logo, 200, screenHeight / 2, WHITE);

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        if (!(IsKeyDown(KEY_BACKSPACE))) {
            backspaceHoldDown = 0;
            backspaceCounter = 0;
        }


        BeginDrawing();

        Color backgroundColor = { 225, 225, 225, 255};
        Color loginButtonColor = { 6, 125, 155, 255};
        Color loginButtonColorPressed = { 6, 110, 137, 255 };

        

        DrawTextEx(customFont, "PATENT BANK", Vector2{ (float)15.0f, 20.0f }, 40, 2, BLACK);

        //Color inputBorderColor = { 240, 240, 240, 90 };
        ClearBackground(backgroundColor);


        ///////////////////// EMAIL INPUT /////////////////////
        DrawTextEx(customFont, "Email:", Vector2{ (float)15, (float)loginHeight / 2 - 125 }, 20, 2, BLACK);
        DrawRectangle(15, loginHeight / 2 - 100, 275, 30, WHITE);
        if (CheckCollisionPointRec(GetMousePosition(), emailInputBox) || isTypingGlobal[0] == 1) {
            isTypingGlobal[0] = getInput(emailInputBox, isTypingGlobal[0], emailInput, charCountGlobal[0]);
        }
        DrawRectangleLines((int)emailInputBox.x, (int)emailInputBox.y, (int)emailInputBox.width, (int)emailInputBox.height, DARKGRAY);
        DrawTextEx(customFont, emailInput, Vector2{ (float)emailInputBox.x + 5, (float)emailInputBox.y + 4 }, 20, 2, BLACK);
        if (isTypingGlobal[0] == 1)
        {
            if (((framesCounter / 20) % 2) == 0) DrawText("|", (int)emailInputBox.x + 8 + MeasureText(emailInput, 20), (int)emailInputBox.y + 6, 20, BLACK);
 
        }
        
        ///////////////////////////////////////////////////////
        DrawTexture(logo, 200, screenHeight / 2, BLACK);

        ///////////////////// PASSWORD INPUT //////////////////
        DrawTextEx(customFont, "Password:", Vector2{ (float)15, (float)loginHeight / 2 - 50 }, 20, 2, BLACK);
        DrawRectangle(15, loginHeight / 2 - 25, 275, 30, WHITE);

        if (CheckCollisionPointRec(GetMousePosition(), passwordInputBox)) DrawRectangleLines((int)passwordInputBox.x, (int)passwordInputBox.y, (int)passwordInputBox.width, (int)passwordInputBox.height, BLACK);
        else DrawRectangleLines((int)passwordInputBox.x, (int)passwordInputBox.y, (int)passwordInputBox.width, (int)passwordInputBox.height, DARKGRAY);

        DrawText(passwordInputHidden, (int)passwordInputBox.x + 5, (int)passwordInputBox.y + 4, 20, BLACK);

        

        ///////////////////////////////////////////////////////
        if ((isTypingGlobal[0] == 0 && isTypingGlobal[1] == 0) || (framesCounter > 40))
        {
            framesCounter = 0;
        }
        if (isTypingGlobal[0] == 0)
        {
            DrawTextEx(customFont, "Password:", Vector2{ (float)15, (float)loginHeight / 2 - 50 }, 20, 2, RED);
        }
      

                DrawTextEx(customFont, ("Frame time: " + to_string(framesCounter)).c_str(), Vector2{ (float)155, (float)loginHeight / 2 - 125 }, 20, 2, BLACK);


        // LOGIN BUTTON
        DrawRectangle(15, loginHeight / 2 + 50, 275, 40, loginButtonColor);
        
        if (CheckCollisionPointRec(GetMousePosition(), { 15, loginHeight / 2 + 50, 250, 40 }))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                return true;
            }
            DrawRectangle(15, loginHeight / 2 + 50, 275, 40, loginButtonColorPressed);
        }
        DrawTextEx(customFont, "Login", Vector2{ (float)loginWidth / 2 - (float)172.5, (float)loginHeight / 2 + 60 }, 20, 2, WHITE);

        // SIGN UP BUTTON

        DrawRectangle(15, loginHeight / 2 + 110, 275, 40, loginButtonColor);

        if (CheckCollisionPointRec(GetMousePosition(), { 15, loginHeight / 2 + 110, 250, 40 }))
        {
            DrawRectangle(15, loginHeight / 2 + 110, 275, 40, loginButtonColorPressed);
        }
        DrawTextEx(customFont, "Sign up", Vector2{ (float)loginWidth / 2 - (float)180, (float)loginHeight / 2 + 120 }, 20, 2, WHITE);

        DrawTexture(logo, 375, 135, WHITE);

     

        EndDrawing();
    }

    return false;

}


bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}