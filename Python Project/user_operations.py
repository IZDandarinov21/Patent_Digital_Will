from user_authentication import authenticate_user, get_user_pin
from account_operations import create_account

def initialize_user(list_of_card_holders):
    while True:
        print("Do you have an account?")
        print("1. Yes")
        print("2. No, create a new account")

        try:
            choice = int(input("Enter your choice (1-2): ").strip())
            if choice == 1:
                current_user = authenticate_user(list_of_card_holders)
                break
            elif choice == 2:
                create_account(list_of_card_holders)
                current_user = authenticate_user(list_of_card_holders)
                break
            else:
                print("Invalid choice. Please enter 1 or 2.")
        except ValueError:
            print("Invalid input. Please enter a valid choice.")

    if get_user_pin(current_user):
        print("Welcome ", current_user.get_firstName(), " :)")
    return current_user
