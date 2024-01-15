from colorama import Fore, Style
from bank_operations import deposit, withdrawal, pay_basic_expenses, check_balance_and_transaction_history, transfer
from account_operations import change_user_info, close_account
from saving_account_operations import savings_account
def print_colored_menu():
    print(Fore.CYAN + Style.BRIGHT + """
    ********************************************
    *   Please choose from the following menu   *
    ********************************************
    """ + Style.RESET_ALL)
    print("1. " + Fore.GREEN + "Deposit" + Style.RESET_ALL)
    print("2. " + Fore.GREEN + "Withdrawal" + Style.RESET_ALL)
    print("3. " + Fore.GREEN + "Pay Basic Expenses" + Style.RESET_ALL)
    print("4. " + Fore.GREEN + "Show Balance and Transactions History" + Style.RESET_ALL)
    print("5. " + Fore.GREEN + "Transfer" + Style.RESET_ALL)
    print("6. " + Fore.GREEN + "Change User Information" + Style.RESET_ALL)
    print("7. " + Fore.GREEN + "Savings Account" + Style.RESET_ALL)
    print("8. " + Fore.RED + "Close Account" + Style.RESET_ALL)
    print("9. " + Fore.RED + "Exit" + Style.RESET_ALL)

def process_menu_option(option, current_user, list_of_card_holders):
    if option == 1:
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
        print(Fore.YELLOW + Style.BRIGHT + "Thank you for choosing us!" + Style.RESET_ALL)
        return False
    elif option == 9:
        print(Fore.YELLOW + Style.BRIGHT + """
        ********************************************
        *                                           *
        *        Thank you for choosing us!        *
        *        Have a nice day!                   *
        *                                          *
        ********************************************
        """ + Style.RESET_ALL)
        return False
    else:
        print(Fore.RED + "Invalid option. Please try again." + Style.RESET_ALL)
    return True
