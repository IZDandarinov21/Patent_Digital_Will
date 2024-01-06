# main.py

from bank_operations import print_menu, deposit, withdrawal, check_balance, transfer
from user_authentication import authenticate_user, get_user_pin

def main():
    current_user = authenticate_user()

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
            deposit(current_user)
        elif option == 2:
            withdrawal(current_user)
        elif option == 3:
            check_balance(current_user)
        elif option == 4:
            transfer(current_user)
        elif option == 5:
            print("Thank you for choosing us!")
            break
        else:
            print("Invalid option. Please try again.")

    print("Thank you for . Have a nice day :)")


if __name__ == "__main__":
    main()
