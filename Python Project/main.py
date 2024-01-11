# main.py
from menu import print_menu
from account_operations import create_account, close_account, change_user_info
from user_authentication import authenticate_user, get_user_pin, load_card_holders_from_json
from saving_account_operations import savings_account
from bank_operations import deposit, withdrawal, transfer, check_balance_and_transaction_history, pay_basic_expenses

def main():
    list_of_card_holders = load_card_holders_from_json('card_holders.json')

    # Ask the user if they have an account or want to create a new one
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

    while True:
        print_menu()
        try:
            option = int(input())
        except ValueError:
            print("Invalid input. Please try again. ")
            continue

        if   option == 1:
            deposit(current_user, list_of_card_holders)
        elif option == 2:
            withdrawal(current_user, list_of_card_holders)
        elif option == 3:
            pay_basic_expenses(current_user, list_of_card_holders)
        elif option == 4:
            check_balance_and_transaction_history(current_user)
        elif option == 5:
            transfer(current_user, list_of_card_holders)
        elif option == 6:
            change_user_info(current_user, list_of_card_holders)
        elif option == 7:
            savings_account(current_user, list_of_card_holders)
        elif option == 8:
            close_account(current_user, list_of_card_holders)
            print("Thank you for choosing us!")
            break
        elif option == 9:
            print("Exiting the program. Have a nice day!")
            break
        else:
            print("Invalid option. Please try again.")

    print("Have a nice day :)")

if __name__ == "__main__":
    main()
