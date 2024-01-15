# bank_operations.py
from colorama import Fore, Style
from user_authentication import get_user_by_names
from user_authentication import  save_card_holders_to_json


def print_deposit_ascii_art():
    print(Fore.CYAN + Style.BRIGHT + """
    ************************************
       Deposit Money to Your Account
    ************************************
    """ + Style.RESET_ALL)


def deposit(card_holder, list_of_card_holders):
    try:
        print_deposit_ascii_art()

        deposit_amount = float(input("How much do you like to deposit: "))
        card_holder.set_balance(card_holder.get_balance() + deposit_amount)
        card_holder.add_to_history("Deposit", deposit_amount)

        print(
            Fore.GREEN + f"Thank you for your money! Your balance is: {card_holder.get_balance()} BGN" + Style.RESET_ALL)

        # Save updated data to JSON file after deposit
        save_card_holders_to_json(list_of_card_holders, 'card_holders.json')

        print(Fore.MAGENTA + Style.BRIGHT + """
        ********************************************
              Enjoy Your Day with Terminal Bank!
        ********************************************
        """ + Style.RESET_ALL)

    except ValueError:
        print(Fore.RED + "Invalid input. Please enter a valid amount." + Style.RESET_ALL)


def print_withdrawal_ascii_art():
    print(Fore.CYAN + Style.BRIGHT + """
    **************************************
       Withdraw Money from Your Account
    **************************************
    """ + Style.RESET_ALL)


def withdrawal(card_holder, list_of_card_holders):
    try:
        print_withdrawal_ascii_art()

        withdrawal_amount = float(input("How much do you like to withdraw: "))

        if card_holder.get_balance() < withdrawal_amount:
            print(Fore.RED + "Insufficient balance. Withdrawal canceled." + Style.RESET_ALL)
        else:
            card_holder.set_balance(card_holder.get_balance() - withdrawal_amount)
            card_holder.add_to_history("Withdrawal", withdrawal_amount)

            print(Fore.GREEN + f"You're good to go! Your balance is: {card_holder.get_balance()} BGN" + Style.RESET_ALL)

            # Save updated data to JSON file after withdrawal
            save_card_holders_to_json(list_of_card_holders, 'card_holders.json')

            print(Fore.MAGENTA + Style.BRIGHT + """
            ********************************************
                  Enjoy Your Day with Terminal Bank!
            ********************************************
            """ + Style.RESET_ALL)

    except ValueError:
        print(Fore.RED + "Invalid input. Please enter a valid amount." + Style.RESET_ALL)




def check_balance_and_transaction_history(card_holder):
    print(Fore.CYAN + Style.BRIGHT + """
    ******************************************************
                    Account Balance and History
    ******************************************************
    """ + Style.RESET_ALL)

    print("Your current balance is: ", card_holder.get_balance())
    print("\nTransaction History:")

    for transaction_type, amount, currency in card_holder.get_transaction_history():
        print(f"{Fore.YELLOW}{transaction_type}:{Fore.GREEN} {amount} {currency}{Style.RESET_ALL}")

    print(Fore.MAGENTA + Style.BRIGHT + """
                ********************************************
                      Enjoy Your Day with Terminal Bank!
                ********************************************
                """ + Style.RESET_ALL)


EXCHANGE_RATES = {'USD': 1.79, 'EUR': 1.96}

def print_transfer_ascii_art():
    print(Fore.CYAN + Style.BRIGHT + """
    ****************************************
               Transfer Money
    ****************************************
    """ + Style.RESET_ALL)

def transfer(current_user, list_of_card_holders):
    print_transfer_ascii_art()

    receiver_first_name = input("Enter receiver's first name: ")
    receiver_last_name = input("Enter receiver's last name: ")
    receiver_card_number = input("Enter receiver's card number: ")

    receiver = get_user_by_names(receiver_first_name, receiver_last_name, receiver_card_number, list_of_card_holders)

    if not receiver:
        print("Receiver not found.")
        return

    try:
        transfer_amount = float(input("Enter the amount to transfer: "))

        print("Choose the account from which you want to transfer:")
        print("1. Spending Account")
        print("2. Savings Account")

        choice = int(input("Enter your choice (1-2): ").strip())

        chosen_currency = None  # Declare chosen_currency outside the if block

        if choice == 1:
            # Transfer from spending account to receiver's spending account
            if current_user.get_balance() < transfer_amount:
                print(Fore.RED + "Insufficient balance. Transfer canceled." + Style.RESET_ALL)
                return

            current_user.subtract_from_balance(transfer_amount)
            receiver.add_to_balance(transfer_amount)

            chosen_currency = 'BGN'

            print(Fore.GREEN + "Transfer successful!" + Style.RESET_ALL)
            print(f"Sender's Spending Account Balance: {current_user.get_balance()} BGN")
            print(f"Receiver's Spending Account Balance: {receiver.get_balance()} BGN")

        elif choice == 2:
            # Transfer from savings account to receiver's spending account
            print("Choose the currency of the savings account:")
            print("1. BGN")
            print("2. USD")
            print("3. EUR")

            currency_choice = int(input("Enter your currency choice (1-3): ").strip())

            if currency_choice not in [1, 2, 3]:
                print(Fore.RED + "Invalid currency choice. Transfer canceled." + Style.RESET_ALL)
                return

            currency_mapping = {1: 'BGN', 2: 'USD', 3: 'EUR'}
            chosen_currency = currency_mapping[currency_choice]

            sender_savings_balance = current_user.get_savings_balance(chosen_currency)

            if sender_savings_balance < transfer_amount:
                print(Fore.RED + "Insufficient balance in the chosen currency. Transfer canceled." + Style.RESET_ALL)
                return

            # Update this part to handle transfers in USD and EUR
            if chosen_currency == 'BGN':
                current_user.subtract_from_savings_bgn(transfer_amount)
                receiver.add_to_balance(transfer_amount)
            elif chosen_currency == 'USD':
                current_user.subtract_from_savings_usd(transfer_amount)
                receiver.add_to_balance(transfer_amount * EXCHANGE_RATES['USD'])
            elif chosen_currency == 'EUR':
                current_user.subtract_from_savings_eur(transfer_amount)
                receiver.add_to_balance(transfer_amount * EXCHANGE_RATES['EUR'])

            print(Fore.GREEN + "Transfer successful!" + Style.RESET_ALL)
            print(f"Sender's {chosen_currency} Savings Account Balance: {sender_savings_balance - transfer_amount} {chosen_currency}")
            print(f"Receiver's Spending Account Balance: {receiver.get_balance()} BGN")

        else:
            print(Fore.RED + "Invalid choice. Transfer canceled." + Style.RESET_ALL)

        # Save updated data to JSON file after the transfer
        save_card_holders_to_json(list_of_card_holders, 'card_holders.json')

        # Add transactions to the transaction history
        current_user.add_to_history(f"Transfer to {receiver_first_name} {receiver_last_name} ({receiver_card_number})", -transfer_amount, chosen_currency)
        receiver.add_to_history(f"Transfer from {current_user.get_firstName()} {current_user.get_lastName()} ({current_user.get_cardNum()})", transfer_amount, chosen_currency)

        print(Fore.MAGENTA + Style.BRIGHT + """
                ********************************************
                        Have a Great Day with Terminal Bank!
                ********************************************
                """ + Style.RESET_ALL)

    except ValueError:
        print(Fore.RED + "Invalid input. Please enter a valid amount." + Style.RESET_ALL)



def print_expenses_end_ascii_art():
    print(Fore.MAGENTA + Style.BRIGHT + """
    **************************************************
                 Expenses Payment Completed
    **************************************************
    """ + Style.RESET_ALL)

def pay_basic_expenses(current_user, list_of_card_holders):
    print_expenses_end_ascii_art()

    expense_options = {
        1: ("Water Bill", "water", 50.0),
        2: ("Electricity Bill", "electricity", 100.0),
        3: ("Internet Bill", "internet", 30.0),
        4: ("Tax Bills", "tax", 400.0),
        5: ("Pay all taxes", "all", 580)  # Adding a default value for tax
    }

    # Display available expense options
    print("Choose an expense to pay:")
    for option, (expense_name, _, expense_amount) in expense_options.items():
        print(f"{option}. {expense_name} - Amount: {expense_amount} BGN")

    try:
        choice = int(input("Enter your choice (1-4): ").strip())

        if choice == 4:
            # Paying taxes
            taxes = {
                1: ("Property Tax", "property_tax", 200.0),
                2: ("Income Tax", "income_tax", 150.0),
                3: ("Sales Tax", "sales_tax", 50.0),
                4: ("All Taxes", "all_taxes", 400.0)
                # Add more taxes as needed
            }

            print("Choose a tax to pay:")
            for tax_option, (tax_name, _, tax_amount) in taxes.items():
                print(f"{tax_option}. {tax_name} - Amount: {tax_amount} BGN")

            tax_choice = int(input("Enter your tax choice (1-4): ").strip())

            if tax_choice in taxes:
                tax_name, tax_code, tax_amount = taxes[tax_choice]

                # Check if the user has sufficient balance
                if current_user.get_balance() < tax_amount:
                    print(Fore.RED + "Insufficient balance. Tax payment canceled." + Style.RESET_ALL)
                    return

                print(f"{tax_name} payment of {tax_amount} BGN confirmed!")

                # Deduct the amount from the user's balance
                current_user.set_balance(current_user.get_balance() - tax_amount)
                current_user.add_to_history(f"Tax Payment - {tax_name}", tax_amount)

                print(Fore.GREEN + "Payment successful!" + Style.RESET_ALL)
                print(f"Remaining balance: {current_user.get_balance()} BGN")

                # Save updated data to JSON file after tax payment
                save_card_holders_to_json(list_of_card_holders, 'card_holders.json')

            else:
                print(Fore.RED + "Invalid tax choice. Tax payment canceled." + Style.RESET_ALL)
                return

        elif choice in expense_options:
            expense_name, expense_code, expense_amount = expense_options[choice]

            # Check if the user has sufficient balance
            if current_user.get_balance() < expense_amount:
                print(Fore.RED + "Insufficient balance. Bill payment canceled." + Style.RESET_ALL)
                return

            print(f"{expense_name} payment of {expense_amount} BGN confirmed!")

            # Deduct the amount from the user's balance
            current_user.set_balance(current_user.get_balance() - expense_amount)
            current_user.add_to_history(f"Bill Payment - {expense_name}", expense_amount)

            print(Fore.GREEN + "Payment successful!" + Style.RESET_ALL)
            print(f"Remaining balance: {current_user.get_balance()} BGN")

            # Save updated data to JSON file after bill payment
            save_card_holders_to_json(list_of_card_holders, 'card_holders.json')

        else:
            print(Fore.RED + "Invalid choice. Bill payment canceled." + Style.RESET_ALL)

    except ValueError:
        print(Fore.RED + "Invalid input. Please enter a valid choice." + Style.RESET_ALL)

    print_expenses_end_ascii_art()
    print(Fore.MAGENTA + Style.BRIGHT + """
                ********************************************
                        Have a Great Day with Terminal Bank!
                ********************************************
                """ + Style.RESET_ALL)















