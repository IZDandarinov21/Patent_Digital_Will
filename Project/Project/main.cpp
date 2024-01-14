#include "Header.h"

void main()
{

    InitWindow(loginWidth, loginHeight, "PATENT BANK | PLEASE LOG IN . . .");
    bool loginSuccess = login();
    CloseWindow();
    app();


    //CloseWindow();
}