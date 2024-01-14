#include "Header.h"
#define MAX_INPUT_CHARS 24

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

bool login()
{
        Font customFont = LoadFont("../assets/lato.ttf");

    // Sample login info

    LOGIN_INFO accounts[10];
    accounts[0].email = "joro@gmail.com";
    accounts[0].password = "123456";

    bool isTyping[2] = { 0 , 0 };

    // EMAIL INPUT BOX
    char emailInput[MAX_INPUT_CHARS + 1] = "\0";
    int emailCharCount = 0;

    // LOGIN INPUT BOX
    char passwordInput[MAX_INPUT_CHARS + 1] = "\0";
    char passwordInputHidden[MAX_INPUT_CHARS + 1] = "\0";
    int passwordCharCount = 0;


    int backspaceHoldDown = 0;

    Rectangle emailInputBox = { 15, loginHeight / 2 - 100, 275, 30 };
    Rectangle passwordInputBox = { 15, loginHeight / 2 - 25, 275, 30 };

    int backspaceCounter = 0;
    int emailFramesCounter = 0;
    int passwordFramesCounter = 0;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        ///////////////////// EMAIL INPUT /////////////////////
        if (CheckCollisionPointRec(GetMousePosition(), emailInputBox))
        {  
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && isTyping[0] == 0)
            {
                isTyping[0] = 1;
            }
        }

        else if (isTyping[0] == 1 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            isTyping[0] = 0;
        }

        if(CheckCollisionPointRec(GetMousePosition(), emailInputBox)) SetMouseCursor(MOUSE_CURSOR_IBEAM);
        if (isTyping[0] == 1)
        {        

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (emailCharCount < MAX_INPUT_CHARS))
                {
                    emailInput[emailCharCount] = (char)key;
                    emailInput[emailCharCount + 1] = '\0'; // Add null terminator at the end of the string.
                    emailCharCount++;
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
                        emailCharCount--;
                        if (emailCharCount < 0) emailCharCount = 0;
                        emailInput[emailCharCount] = '\0';
                        backspaceHoldDown = 0;
                    }

                }
                backspaceCounter++;
            }


            if (IsKeyPressed(KEY_BACKSPACE))
            {
                emailCharCount--;
                if (emailCharCount < 0) emailCharCount = 0;
                emailInput[emailCharCount] = '\0';
            }
        }
        if (isTyping[0] == 1) emailFramesCounter++;
        else emailFramesCounter = 0;
        ///////////////////////////////////////////////////////



        ///////////////////// PASSWORD INPUT //////////////////
        if (CheckCollisionPointRec(GetMousePosition(), passwordInputBox))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && isTyping[1] == 0)
            {
                isTyping[1] = 1;
            }
        }

        else if (isTyping[1] == 1 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            isTyping[1] = 0;
        }

        if (CheckCollisionPointRec(GetMousePosition(), passwordInputBox)) SetMouseCursor(MOUSE_CURSOR_IBEAM);
            
        if (isTyping[1] == 1)
        {

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (passwordCharCount < MAX_INPUT_CHARS))
                {
                    passwordInput[passwordCharCount] = (char)key;
                    passwordInputHidden[passwordCharCount] = '*';
                    passwordInput[passwordCharCount + 1] = '\0'; // Add null terminator at the end of the string.
                    passwordCharCount++;
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
                        passwordCharCount--;
                        if (passwordCharCount < 0) passwordCharCount = 0;
                        passwordInput[passwordCharCount] = '\0';
                        passwordInputHidden[passwordCharCount] = '\0';
                        backspaceHoldDown = 0;
                    }

                }
                backspaceCounter++;
            }


            if (IsKeyPressed(KEY_BACKSPACE))
            {
                passwordCharCount--;
                if (passwordCharCount < 0) passwordCharCount = 0;
                passwordInput[passwordCharCount] = '\0';
                passwordInputHidden[passwordCharCount] = '\0';
            }

        }
        if (isTyping[1] == 1) passwordFramesCounter++;
        else passwordFramesCounter = 0;
        ///////////////////////////////////////////////////////

        if (!(IsKeyDown(KEY_BACKSPACE))) {
            backspaceHoldDown = 0;
            backspaceCounter = 0;
        }
        BeginDrawing();

        Color backgroundColor = { 225, 225, 225, 255};
        Color loginButtonColor = { 6, 125, 155, 255};
        Color loginButtonColorPressed = { 6, 110, 137, 255 };

        



        //Color inputBorderColor = { 240, 240, 240, 90 };
        ClearBackground(backgroundColor);


        ///////////////////// EMAIL INPUT /////////////////////
        DrawTextEx(customFont, "Email:", Vector2{ (float)15, (float)loginHeight / 2 - 125 }, 20, 2, BLACK);
        DrawRectangle(15, loginHeight / 2 - 100, 275, 30, WHITE);

        if (isTyping[0] == 1) DrawRectangleLines((int)emailInputBox.x, (int)emailInputBox.y, (int)emailInputBox.width, (int)emailInputBox.height, BLACK);
        else DrawRectangleLines((int)emailInputBox.x, (int)emailInputBox.y, (int)emailInputBox.width, (int)emailInputBox.height, DARKGRAY);

        DrawTextEx(customFont, emailInput, Vector2{ (float)emailInputBox.x + 5, (float)emailInputBox.y + 4 }, 20, 2, BLACK);

        if (isTyping[0] == 1)
        {
            if (emailCharCount < MAX_INPUT_CHARS)
            {
                // Draw blinking char
                if (((emailFramesCounter / 20) % 2) == 0) DrawText("|", (int)emailInputBox.x + 8 + MeasureText(emailInput, 20), (int)emailInputBox.y + 6, 20, BLACK);
            }
        }
        ///////////////////////////////////////////////////////


        ///////////////////// PASSWORD INPUT //////////////////
        DrawTextEx(customFont, "Password:", Vector2{ (float)15, (float)loginHeight / 2 - 50 }, 20, 2, BLACK);
        DrawRectangle(15, loginHeight / 2 - 25, 275, 30, WHITE);

        if (CheckCollisionPointRec(GetMousePosition(), passwordInputBox)) DrawRectangleLines((int)passwordInputBox.x, (int)passwordInputBox.y, (int)passwordInputBox.width, (int)passwordInputBox.height, BLACK);
        else DrawRectangleLines((int)passwordInputBox.x, (int)passwordInputBox.y, (int)passwordInputBox.width, (int)passwordInputBox.height, DARKGRAY);

        DrawText(passwordInputHidden, (int)passwordInputBox.x + 5, (int)passwordInputBox.y + 4, 20, BLACK);

        if (isTyping[1] == 1)
        {
            if (passwordCharCount < MAX_INPUT_CHARS)
            {
                // Draw blinking char
                if (((passwordFramesCounter / 20) % 2) == 0) DrawText("|", (int)passwordInputBox.x + 8 + MeasureText(passwordInputHidden, 20), (int)passwordInputBox.y + 6, 20, BLACK);
            }
        }

        ///////////////////////////////////////////////////////

        // LOGIN BUTTON
        DrawRectangle(15, loginHeight / 2 + 50, 250, 40, loginButtonColor);
        
        if (CheckCollisionPointRec(GetMousePosition(), { 15, loginHeight / 2 + 50, 250, 40 }))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                return true;
            }
            DrawRectangle(15, loginHeight / 2 + 50, 250, 40, loginButtonColorPressed);
        }
        DrawTextEx(customFont, "Login", Vector2{ (float)loginWidth / 2 - 185, (float)loginHeight / 2 + 60 }, 20, 2, WHITE);

        // SIGN UP BUTTON

        DrawRectangle(15, loginHeight / 2 + 110, 250, 40, loginButtonColor);

        if (CheckCollisionPointRec(GetMousePosition(), { 15, loginHeight / 2 + 110, 250, 40 }))
        {
            DrawRectangle(15, loginHeight / 2 + 110, 250, 40, loginButtonColorPressed);
        }
        DrawTextEx(customFont, "Sign up", Vector2{ (float)loginWidth / 2 - (float)192.5, (float)loginHeight / 2 + 120 }, 20, 2, WHITE);




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