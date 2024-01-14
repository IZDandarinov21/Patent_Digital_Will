#include "Header.h"
#include <string>

enum class TransactionState {
    NONE,
    DEPOSIT,
    WITHDRAWAL
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

    std::string amountInput = "";
    double balance = 0.0;
    TransactionState transactionState = TransactionState::NONE;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Check if the deposit button was clicked
        if (CheckCollisionPointRec(GetMousePosition(), depositButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            transactionState = TransactionState::DEPOSIT;
        }

        // Check if the withdrawal button was clicked
        if (CheckCollisionPointRec(GetMousePosition(), withdrawalButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            transactionState = TransactionState::WITHDRAWAL;
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

        // Draw transaction window
        if (transactionState != TransactionState::NONE)
        {
            Rectangle transactionWindow = { screenWidth / 4, screenHeight / 4, screenWidth / 2, screenHeight / 2 };

            DrawRectangleRec(transactionWindow, LIGHTGRAY);
            DrawText((transactionState == TransactionState::DEPOSIT ? "Deposit" : "Withdrawal"), screenWidth / 2 - 50, screenHeight / 4 + 10, 20, BLACK);
            DrawText("Enter amount:", screenWidth / 2 - 80, screenHeight / 4 + 50, 20, BLACK);
            DrawText(amountInput.c_str(), screenWidth / 2 - 80, screenHeight / 4 + 80, 20, BLACK);

            // Check if the mouse is within the transaction window
            if (!IsMouseInRect(transactionWindow))
            {
                transactionState = TransactionState::NONE;
                amountInput = "";
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

                amountInput = "";
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
