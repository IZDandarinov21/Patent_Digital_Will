#include "Header.h"
#include <string>
#include <iostream>
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

    Rectangle depositButton = { screenWidth / 2 - 100, screenHeight / 2, 200, 50 };
    Rectangle withdrawalButton = { screenWidth / 2 - 100, screenHeight / 2 + 60, 200, 50 };
    Rectangle makeWillButton = { screenWidth / 2 - 100, screenHeight / 2 + 120, 200, 50 };

    std::string amountInput = "";
    std::string recipientInput = "";
    double balance = 0.0;
    TransactionState transactionState = TransactionState::NONE;

    bool makeWillButtonClicked = false;

    std::vector<std::string> users = { "User1", "User2", "User3" };  // Replace with your user list

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

        DrawText("Patent Bank", 10, 10, 20, LIGHTGRAY);
        DrawText(("Hi, User, Balance: " + std::to_string(balance)).c_str(), screenWidth / 2, 10, 20, LIGHTGRAY);

        // Draw buttons
        DrawRectangleRec(depositButton, LIGHTGRAY);
        DrawText("Deposit", depositButton.x + 70, depositButton.y + 15, 20, BLACK);

        DrawRectangleRec(withdrawalButton, LIGHTGRAY);
        DrawText("Withdraw", withdrawalButton.x + 60, withdrawalButton.y + 15, 20, BLACK);

        DrawRectangleRec(makeWillButton, LIGHTGRAY);
        DrawText("Make My Will", makeWillButton.x + 25, makeWillButton.y + 15, 20, BLACK);

        // Draw transaction window
        if (transactionState != TransactionState::NONE)
        {
            Rectangle transactionWindow = { screenWidth / 4, screenHeight / 4, screenWidth / 2, screenHeight / 2 };

            DrawRectangleRec(transactionWindow, LIGHTGRAY);
            DrawText((transactionState == TransactionState::DEPOSIT ? "Deposit" :
                (transactionState == TransactionState::WITHDRAWAL ? "Withdrawal" : "Make My Will")),
                screenWidth / 2 - 80, screenHeight / 4 + 10, 20, BLACK);

            if (transactionState != TransactionState::MAKE_WILL)
            {
                DrawText("Enter amount:", screenWidth / 2 - 80, screenHeight / 4 + 50, 20, BLACK);
                DrawText(amountInput.c_str(), screenWidth / 2 - 80, screenHeight / 4 + 80, 20, BLACK);
            }
            else
            {
                DrawText("Enter recipient (username):", screenWidth / 2 - 140, screenHeight / 4 + 50, 20, BLACK);
                DrawText(recipientInput.c_str(), screenWidth / 2 - 80, screenHeight / 4 + 80, 20, BLACK);
            }

            // Check if the mouse is within the transaction window
            if (!IsMouseInRect(transactionWindow) && !makeWillButtonClicked)
            {
                transactionState = TransactionState::NONE;
                amountInput = "";
                recipientInput = "";
            }
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
                }
                else if (transactionState == TransactionState::WITHDRAWAL)
                {
                    if (balance >= transactionAmount)
                    {
                        balance -= transactionAmount;
                    }
                    else
                    {
                        // Handle insufficient balance
                    }
                }
                else if (transactionState == TransactionState::MAKE_WILL)
                {
                    // Implement logic to make a will, e.g., transfer assets to another user
                    // For simplicity, let's just print a message
                    if (!recipientInput.empty())
                    {
                        std::cout << "Will created! Assets transferred to user: " << recipientInput << std::endl;
                    }
                    else
                    {
                        std::cout << "Please enter a valid recipient username." << std::endl;
                    }
                }

                amountInput = "";
                recipientInput = "";
                transactionState = TransactionState::NONE;
            }
            catch (const std::exception& e)
            {
                // Handle or report the exception
            }
        }
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
