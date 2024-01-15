from colorama import Fore, Style
from user_authentication import authenticate_user, get_user_pin
from account_operations import create_account

def print_colored_welcome_banner():
    print(Fore.YELLOW + Style.BRIGHT + """
    ********************************************
    *                                          *
    *   Welcome to the World of Financial Bliss! *
    *               Terminal Bank                *
    *                                          *
    *    Unleash Your Dreams with Terminal Bank! *
    *                                          *
    ********************************************
    """ + Style.RESET_ALL)

def initialize_user(list_of_card_holders):
    print_colored_welcome_banner()

    while True:
        print("Do you have an account?")
        print("1. " + Fore.GREEN + "Yes" + Style.RESET_ALL)
        print("2. " + Fore.BLUE + "No, create a new account" + Style.RESET_ALL)

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
                print(Fore.RED + "Invalid choice. Please enter 1 or 2." + Style.RESET_ALL)
        except ValueError:
            print(Fore.RED + "Invalid input. Please enter a valid choice." + Style.RESET_ALL)

    if get_user_pin(current_user):
        print(Fore.GREEN + Style.BRIGHT + """
        ********************************************
          Welcome to Terminal Bank, {user_first_name}! :)
        ********************************************
        """.format(user_first_name=current_user.get_firstName()) + Style.RESET_ALL)
    return current_user

