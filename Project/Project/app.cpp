#include "Header.h"
#include <string>
#include <vector>

enum class TransactionState {
    NONE,
    DEPOSIT,
    WITHDRAWAL,
    MAKE_WILL
};

bool IsMouseInRect(const Rectangle& rect) {
    Vector2 mousePos = GetMousePosition();
    return (mousePos.x >= rect.x && mousePos.x <= (rect.x + rect.width) &&
        mousePos.y >= rect.y && mousePos.y <= (rect.y + rect.height));
}

void app()
{
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "PATENT Bank");

    // Load custom font
    Font customFont = LoadFont("../assets/lato.ttf");
    SetTargetFPS(60);

    Rectangle transactionsButton = { 5, 70, 140, 65 };
    Rectangle summaryButton = { 5, 140, 140, 65 };
    Rectangle depositButton = { 5, 220, 140, 50 };
    Rectangle withdrawalButton = { 5, 275, 140, 50 };
    Rectangle sendMoneyButton = { 5, 330, 140, 50 };
    Rectangle logOutButton = { 5, screenHeight - 55, 140, 50 };

    string amountInput = "";
    string recipientInput = "";
    int balance = 1000;
    TransactionState transactionState = TransactionState::NONE;

    bool sendMoneyButtonClicked = false;

    vector<string> messages;
    const int maxMessages = 5;

    Color backgroundColor = { 225, 225, 225, 255 };
    Color blue = { 6, 125, 155, 255 };
    

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Check if the deposit button was clicked
        if (CheckCollisionPointRec(GetMousePosition(), depositButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            transactionState = TransactionState::DEPOSIT;
            sendMoneyButtonClicked = false;
        }

        // Check if the withdrawal button was clicked
        if (CheckCollisionPointRec(GetMousePosition(), withdrawalButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            transactionState = TransactionState::WITHDRAWAL;
            sendMoneyButtonClicked = false;
        }

        // Check if the make will button was clicked
        if (CheckCollisionPointRec(GetMousePosition(), sendMoneyButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            sendMoneyButtonClicked = !sendMoneyButtonClicked;
            if (sendMoneyButtonClicked)
            {
                transactionState = TransactionState::MAKE_WILL;
            }
            else
            {
                transactionState = TransactionState::NONE;
                amountInput = "";
                recipientInput = "";
            }
        }

        // Handle text input for the amount
        int key = GetKeyPressed();
        if (key == KEY_BACKSPACE)
        {
            if (!amountInput.empty())
                amountInput.pop_back();
        }
        else if (key >= 48 && key <= 57) // Check if key is a number
        {
            amountInput += (char)key;
        }

        // Handle text input for the recipient (for making the will)
        if (sendMoneyButtonClicked && (IsKeyPressed(KEY_APOSTROPHE) || (key >= 32 && key <= 126))) // Check if key is a valid character
        {
            recipientInput += (char)key;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(backgroundColor);

        // Use custom font
        DrawTextEx(customFont, "Patent Bank", Vector2{ 5.0f, 17.5f }, 27.5f, 2.0f, BLACK);
        DrawRectangle(0, 60.0f, screenWidth, 5, blue);
        DrawTextEx(customFont, "Welcome, user", Vector2{ 165.0f, 15.0f }, 30.0f, 2.0f, BLACK);
        DrawTextEx(customFont, "Your accounts:", Vector2{ 167.5f, 60.0f }, 20.0f, 2.0f, BLACK);
        //DrawTextEx(customFont, ("Balance: " + to_string(balance) + "$").c_str(), Vector2{7.5f, (float)screenHeight - 75.0f}, 20.0f, 2.0f, BLACK);

        DrawRectangle(0, depositButton.y - 10.0f, 150, 5, blue);
        // Draw buttons
        DrawRectangleRec(transactionsButton, LIGHTGRAY);
        DrawTextEx(customFont, "Transactions", Vector2{ transactionsButton.x + 15.0f, transactionsButton.y + 22.5f }, 20.0f, 2.0f, BLACK);

        DrawRectangleRec(summaryButton, LIGHTGRAY);
        DrawTextEx(customFont, "Summary", Vector2{ summaryButton.x + 27.5f, summaryButton.y + 22.5f }, 20.0f, 2.0f, BLACK);

        DrawRectangleRec(depositButton, LIGHTGRAY);
        DrawTextEx(customFont, "Deposit", Vector2{ depositButton.x + 35.0f, depositButton.y + 15.0f }, 20.0f, 2.0f, BLACK);

        DrawRectangleRec(withdrawalButton, LIGHTGRAY);
        DrawTextEx(customFont, "Withdraw", Vector2{ withdrawalButton.x + 25.0f, withdrawalButton.y + 15.0f }, 20.0f, 2.0f, BLACK);

        DrawRectangleRec(sendMoneyButton, LIGHTGRAY);
        DrawTextEx(customFont, "Send money", Vector2{ sendMoneyButton.x + 20.0f, sendMoneyButton.y + 15.0f }, 20.0f, 2.0f, BLACK);

        DrawRectangleRec(logOutButton, LIGHTGRAY);
        DrawRectangle(0, screenHeight - 65, 150, 5, blue);
        DrawTextEx(customFont, "Log out", Vector2{ logOutButton.x + 35.0f, logOutButton.y + 15.0f }, 20.0f, 2.0f, BLACK);

        DrawRectangle(150, 0, 5, screenHeight, blue);

        // Draw transaction window
        if (transactionState != TransactionState::NONE)
        {
            Rectangle transactionWindow = { screenWidth / 4, screenHeight / 4, screenWidth / 2, screenHeight / 2 };

            DrawRectangleRec(transactionWindow, LIGHTGRAY);
            DrawTextEx(customFont, (transactionState == TransactionState::DEPOSIT ? "Deposit" :
                (transactionState == TransactionState::WITHDRAWAL ? "Withdrawal" : "Make My Will")),
                Vector2{ screenWidth / 2 - 80.0f, screenHeight / 4 + 10.0f }, 20.0f, 2.0f, BLACK);

            if (transactionState != TransactionState::MAKE_WILL)
            {
                DrawTextEx(customFont, "Enter amount:", Vector2{ screenWidth / 2 - 80.0f, screenHeight / 4 + 50.0f }, 20.0f, 2.0f, BLACK);
                DrawTextEx(customFont, amountInput.c_str(), Vector2{ screenWidth / 2 - 80.0f, screenHeight / 4 + 80.0f }, 20.0f, 2.0f, BLACK);
            }
            else
            {
                DrawTextEx(customFont, "Enter recipient (username):", Vector2{ screenWidth / 2 - 140.0f, screenHeight / 4 + 50.0f }, 20.0f, 2.0f, BLACK);
                DrawTextEx(customFont, recipientInput.c_str(), Vector2{ screenWidth / 2 - 80.0f, screenHeight / 4 + 80.0f }, 20.0f, 2.0f, BLACK);
            }

            // Check if the mouse is within the transaction window
            if (!IsMouseInRect(transactionWindow) && !sendMoneyButtonClicked)
            {
                transactionState = TransactionState::NONE;
                amountInput = "";
                recipientInput = "";
            }
        }

        // Draw messages
        for (size_t i = 0; i < messages.size(); ++i)
        {
            DrawTextEx(customFont, messages[i].c_str(), Vector2{ 10.0f, screenHeight - 30.0f - (20.0f * i) }, 20.0f, 2.0f, BLACK);
        }

        // TODO: Add more interface elements here

        EndDrawing();
        //----------------------------------------------------------------------------------

        // Perform transaction when Enter key is pressed
        if (IsKeyPressed(KEY_ENTER))
        {
            try
            {
                double transactionAmount = stod(amountInput);

                if (transactionState == TransactionState::DEPOSIT)
                {
                    balance += transactionAmount;
                    messages.insert(messages.begin(), "Deposited: " + to_string(transactionAmount));
                }
                else if (transactionState == TransactionState::WITHDRAWAL)
                {
                    if (balance >= transactionAmount)
                    {
                        balance -= transactionAmount;
                        messages.insert(messages.begin(), "Withdrawn: " + to_string(transactionAmount));
                    }
                    else
                    {
                        messages.insert(messages.begin(), "Insufficient balance for withdrawal.");
                    }
                }
                else if (transactionState == TransactionState::MAKE_WILL)
                {
                    if (!recipientInput.empty())
                    {
                        messages.insert(messages.begin(), "Will created! Assets transferred to user: " + recipientInput);
                    }
                    else
                    {
                        messages.insert(messages.begin(), "Please enter a valid recipient username.");
                    }
                }

                amountInput = "";
                recipientInput = "";
                transactionState = TransactionState::NONE;

                // Limit the number of displayed messages
                if (messages.size() > maxMessages)
                {
                    messages.pop_back();
                }
            }
            catch (const exception& e)
            {
                // Handle or report the exception
                messages.insert(messages.begin(), "Error: Invalid input.");
            }
        }
    }

    // Unload custom font
    UnloadFont(customFont);

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
