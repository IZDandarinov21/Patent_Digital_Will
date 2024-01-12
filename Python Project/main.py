from user_operations import initialize_user
from menu_operations import process_menu_option, print_menu
from user_authentication import load_card_holders_from_json

def main():
    list_of_card_holders = load_card_holders_from_json('card_holders.json')
    current_user = initialize_user(list_of_card_holders)

    while True:
        print_menu()
        try:
            option = int(input())
        except ValueError:
            print("Invalid input. Please try again. ")
            continue

        if not process_menu_option(option, current_user, list_of_card_holders):
            break

    print("Have a nice day :)")

if __name__ == "__main__":
    main()