# main.py

from bank_operations import print_menu, deposit, withdrawal, check_balance, transfer, change_user_info, close_account
from user_authentication import authenticate_user, get_user_pin, load_card_holders_from_json

def main():
    list_of_card_holders = load_card_holders_from_json('card_holders.json')

    current_user = authenticate_user(list_of_card_holders)

    if get_user_pin(current_user):
        print("Welcome ", current_user.get_firstName(), " :)")

    while True:
        print_menu()
        try:
            option = int(input())
        except ValueError:
            print("Invalid input. Please try again. ")
            continue

        if option == 1:
            deposit(current_user, list_of_card_holders)
        elif option == 2:
            withdrawal(current_user, list_of_card_holders)
        elif option == 3:
            check_balance(current_user)
        elif option == 4:
            transfer(current_user, list_of_card_holders)
        elif option == 5:
            change_user_info(current_user, list_of_card_holders)
        elif option == 6:
            close_account(current_user, list_of_card_holders)
            print("Thank you for choosing us!")
            break
        elif option == 7:
            print("Exiting the program. Have a nice day!")
            break
        else:
            print("Invalid option. Please try again.")

        print("Have a nice day :)")

if __name__ == "__main__":
    main()
