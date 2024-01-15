from colorama import Fore, Style
from user_operations import initialize_user
from menu_operations import process_menu_option, print_colored_menu
from user_authentication import load_card_holders_from_json

def print_goodbye_message():
    print(Fore.MAGENTA + Style.BRIGHT + """
    ********************************************
        Have a Nice Day with Terminal Bank!
    ********************************************
    """ + Style.RESET_ALL)

def main():
    list_of_card_holders = load_card_holders_from_json('card_holders.json')
    current_user = initialize_user(list_of_card_holders)

    while True:
        print_colored_menu()
        try:
            option = int(input())
        except ValueError:
            print(Fore.RED + "Invalid input. Please try again." + Style.RESET_ALL)
            continue

        if not process_menu_option(option, current_user, list_of_card_holders):
            break

    print_goodbye_message()

if __name__ == "__main__":
    main()
