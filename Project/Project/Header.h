#pragma once
#include <raylib.h>
#include <iostream>
#include <string>
using namespace std;
const float loginWidth = 600;
const float loginHeight = 400;
const float screenWidth = 1300;
const float screenHeight = 900;
bool login();
void main();
void app();
bool searchAccounts(string input_Email, string input_Password, string emails[], string passwords[]);