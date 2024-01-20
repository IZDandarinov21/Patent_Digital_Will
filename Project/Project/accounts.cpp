#include "Header.h"
struct LOGIN_INFO
{
    string email;
    string password;
};
bool searchAccounts(string input_Email, string input_Password, string emails[], string passwords[])
{
	// search
    for (int i = 0; i < 2; i++)
    {
        if (input_Email == emails[i])
        {
            if (input_Password == passwords[i])
            {
                return true;
            }
        }
    }
    return false;
}