from bank_operations import deposit, withdrawal, pay_basic_expenses, check_balance_and_transaction_history, transfer
from account_operations import change_user_info, close_account
from saving_account_operations import savings_account

def print_menu():
    print("Please choose from one of the following options...")
    print("1. Deposit")
    print("2. Withdrawal")
    print("3. Pay Basic Expenses")
    print("4. Show Balance and Transactions History")
    print("5. Transfer")
    print("6. Change User Information")
    print("7. Saving Account Management")
    print("8. Close Account")
    print("9. Exit")


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
        print("Thank you for choosing us!")
        return False
    elif option == 9:
        print("Exiting the program. Have a nice day!")
        return False
    else:
        print("Invalid option. Please try again.")
    return True
