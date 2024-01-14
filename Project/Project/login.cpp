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
    // Sample login info

    LOGIN_INFO accounts[10];
    accounts[0].email = "joro@gmail.com";
    accounts[0].password = "123456";



    // EMAIL INPUT BOX
    char emailInput[MAX_INPUT_CHARS + 1] = "\0";
    int emailCharCount = 0;

    // LOGIN INPUT BOX
    char passwordInput[MAX_INPUT_CHARS + 1] = "\0";
    int passwordCharCount = 0;


    int backspaceHoldDown = 0;

    Rectangle emailInputBox = { 15, loginHeight / 2 - 100, 275, 30 };
    Rectangle passwordInputBox = { 15, loginHeight / 2 - 25, 275, 30 };

    int backspaceCounter = 0;
    int emailFramesCounter = 0;
    int passwordFramesCounter = 0;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {

        ///////////////////// EMAIL INPUT /////////////////////
        if (CheckCollisionPointRec(GetMousePosition(), emailInputBox))
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

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
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        if (CheckCollisionPointRec(GetMousePosition(), emailInputBox)) emailFramesCounter++;
        else emailFramesCounter = 0;
        ///////////////////////////////////////////////////////



        ///////////////////// PASSWORD INPUT //////////////////
        if (CheckCollisionPointRec(GetMousePosition(), passwordInputBox))
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (passwordCharCount < MAX_INPUT_CHARS))
                {
                    passwordInput[passwordCharCount] = (char)key;
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
            }

        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        if (CheckCollisionPointRec(GetMousePosition(), passwordInputBox)) passwordFramesCounter++;
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
        DrawText("Email:", 15, loginHeight / 2 - 125, 20, BLACK);
        DrawRectangle(15, loginHeight / 2 - 100, 275, 30, WHITE);

        if (CheckCollisionPointRec(GetMousePosition(), emailInputBox)) DrawRectangleLines((int)emailInputBox.x, (int)emailInputBox.y, (int)emailInputBox.width, (int)emailInputBox.height, BLACK);
        else DrawRectangleLines((int)emailInputBox.x, (int)emailInputBox.y, (int)emailInputBox.width, (int)emailInputBox.height, DARKGRAY);

        DrawText(emailInput, (int)emailInputBox.x + 5, (int)emailInputBox.y + 4, 20, BLACK);

        if (CheckCollisionPointRec(GetMousePosition(), emailInputBox))
        {
            if (emailCharCount < MAX_INPUT_CHARS)
            {
                // Draw blinking char
                if (((emailFramesCounter / 20) % 2) == 0) DrawText("|", (int)emailInputBox.x + 8 + MeasureText(emailInput, 20), (int)emailInputBox.y + 6, 20, BLACK);
            }
        }
        ///////////////////////////////////////////////////////


        ///////////////////// PASSWORD INPUT //////////////////
        DrawText("Password:", 15, loginHeight / 2 - 50, 20, BLACK);
        DrawRectangle(15, loginHeight / 2 - 25, 275, 30, WHITE);

        if (CheckCollisionPointRec(GetMousePosition(), passwordInputBox)) DrawRectangleLines((int)passwordInputBox.x, (int)passwordInputBox.y, (int)passwordInputBox.width, (int)passwordInputBox.height, BLACK);
        else DrawRectangleLines((int)passwordInputBox.x, (int)passwordInputBox.y, (int)passwordInputBox.width, (int)passwordInputBox.height, DARKGRAY);

        DrawText(passwordInput, (int)passwordInputBox.x + 5, (int)passwordInputBox.y + 4, 20, BLACK);

        if (CheckCollisionPointRec(GetMousePosition(), passwordInputBox))
        {
            if (passwordCharCount < MAX_INPUT_CHARS)
            {
                // Draw blinking char
                if (((passwordFramesCounter / 20) % 2) == 0) DrawText("|", (int)passwordInputBox.x + 8 + MeasureText(passwordInput, 20), (int)passwordInputBox.y + 6, 20, BLACK);
            }
        }

        ///////////////////////////////////////////////////////

        // LOGIN BUTTON
        DrawRectangle(15, loginHeight / 2 + 50, 250, 40, loginButtonColor);
        
        if (CheckCollisionPointRec(GetMousePosition(), { 15, loginHeight / 2 + 50, 250, 40 }))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if ((convertToString(emailInput) == accounts[0].email) && (convertToString(passwordInput) == accounts[0].password))
                {
                    app();
                }
            }
            DrawRectangle(15, loginHeight / 2 + 50, 250, 40, loginButtonColorPressed);
        }
        DrawText("Login", loginWidth / 2 - 185, loginHeight / 2 + 60, 20, WHITE);

        // SIGN UP BUTTON

        DrawRectangle(15, loginHeight / 2 + 110, 250, 40, loginButtonColor);

        if (CheckCollisionPointRec(GetMousePosition(), { 15, loginHeight / 2 + 110, 250, 40 }))
        {
            DrawRectangle(15, loginHeight / 2 + 110, 250, 40, loginButtonColorPressed);
        }
        DrawText("Sign up", loginWidth / 2 - 195, loginHeight / 2 + 120, 20, WHITE);




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