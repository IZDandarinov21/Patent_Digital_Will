#include "Header.h"
void main()
{
    InitWindow(loginWidth, loginHeight, "PATENT BANK | PLEASE LOG IN . . .");
    bool loginSuccess = login();
    CloseWindow();

    if(loginSuccess) InitWindow(screenWidth, screenHeight, "PATENT Bank");
    while (!WindowShouldClose() && loginSuccess)
    {

    }
    //CloseWindow();
}