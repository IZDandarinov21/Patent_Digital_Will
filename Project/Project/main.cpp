#include "Header.h"
void main()
{
    InitWindow(loginWidth, loginHeight, "Please log in...");
    bool loginSuccess = login();
    CloseWindow();

    if(loginSuccess) InitWindow(screenWidth, screenHeight, "PATENT Bank");
    while (!WindowShouldClose() && loginSuccess)
    {

    }
    //CloseWindow();
}