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

    InitWindow(screenWidth, screenHeight, "Maze Bank");

    // Load custom font
    Font customFont = LoadFont("../assets/lato.ttf");  
    SetTargetFPS(60);

    Rectangle depositButton = { screenWidth / 2 - 100, screenHeight / 2, 200, 50 };
    Rectangle withdrawalButton = { screenWidth / 2 - 100, screenHeight / 2 + 60, 200, 50 };
    Rectangle makeWillButton = { screenWidth / 2 - 100, screenHeight / 2 + 120, 200, 50 };

    std::string amountInput = "";
    std::string recipientInput = "";
    double balance = 0.0;
    TransactionState transactionState = TransactionState::NONE;

    bool makeWillButtonClicked = false;

    std::vector<std::string> messages;
    const int maxMessages = 5;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Check if the deposit button was clicked
        if (CheckCollisionPointRec(GetMousePosition(), depositButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            transactionState = TransactionState::DEPOSIT;
            makeWillButtonClicked = false;
        }

        // Check if the withdrawal button was clicked
        if (CheckCollisionPointRec(GetMousePosition(), withdrawalButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            transactionState = TransactionState::WITHDRAWAL;
            makeWillButtonClicked = false;
        }

        // Check if the make will button was clicked
        if (CheckCollisionPointRec(GetMousePosition(), makeWillButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            makeWillButtonClicked = !makeWillButtonClicked;
            if (makeWillButtonClicked)
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
        if (makeWillButtonClicked && (IsKeyPressed(KEY_APOSTROPHE) || (key >= 32 && key <= 126))) // Check if key is a valid character
        {
            recipientInput += (char)key;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Use custom font
        DrawTextEx(customFont, "Patent Bank", Vector2{ 10.0f, 10.0f }, 20.0f, 2.0f, LIGHTGRAY);
        DrawTextEx(customFont, ("Hi, User, Balance: " + std::to_string(balance)).c_str(), Vector2{ static_cast<float>(screenWidth / 2), 10.0f }, 20.0f, 2.0f, LIGHTGRAY);

        // Draw buttons
        DrawRectangleRec(depositButton, LIGHTGRAY);
        DrawTextEx(customFont, "Deposit", Vector2{ depositButton.x + 70.0f, depositButton.y + 15.0f }, 20.0f, 2.0f, BLACK);

        DrawRectangleRec(withdrawalButton, LIGHTGRAY);
        DrawTextEx(customFont, "Withdraw", Vector2{ withdrawalButton.x + 60.0f, withdrawalButton.y + 15.0f }, 20.0f, 2.0f, BLACK);

        DrawRectangleRec(makeWillButton, LIGHTGRAY);
        DrawTextEx(customFont, "Make My Will", Vector2{ makeWillButton.x + 25.0f, makeWillButton.y + 15.0f }, 20.0f, 2.0f, BLACK);

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
            if (!IsMouseInRect(transactionWindow) && !makeWillButtonClicked)
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
                double transactionAmount = std::stod(amountInput);

                if (transactionState == TransactionState::DEPOSIT)
                {
                    balance += transactionAmount;
                    messages.insert(messages.begin(), "Deposited: " + std::to_string(transactionAmount));
                }
                else if (transactionState == TransactionState::WITHDRAWAL)
                {
                    if (balance >= transactionAmount)
                    {
                        balance -= transactionAmount;
                        messages.insert(messages.begin(), "Withdrawn: " + std::to_string(transactionAmount));
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
            catch (const std::exception& e)
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
