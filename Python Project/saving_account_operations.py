# saving_account_operations.py
from user_authentication import save_card_holders_to_json
from colorama import Fore, Style
EXCHANGE_RATES = {'USD': 1.79, 'EUR': 1.96}



def savings_account(current_user, list_of_card_holders):
    print(Fore.MAGENTA + Style.BRIGHT + """
                    ********************************************
                            Savings Account Management
                    ********************************************
                    """ + Style.RESET_ALL)
    print("1. Transfer from Savings to Spending Account")
    print("2. Deposit to Savings Account")

    try:
        choice = int(input("Enter your choice (1-2): ").strip())

        if choice == 1:
            transfer_from_savings(current_user, list_of_card_holders)
        elif choice == 2:
            deposit_to_savings(current_user, list_of_card_holders)
        else:
            print(Fore.RED + "Invalid choice. Exiting Savings Account Management." + Style.RESET_ALL)
    except ValueError:
        print(Fore.RED + "Invalid input. Please enter a valid choice." + Style.RESET_ALL)

    print(Fore.MAGENTA + Style.BRIGHT + """
                    ********************************************
                            End of Savings Account Management!
                    ********************************************
                    """ + Style.RESET_ALL)




def transfer_from_savings(current_user, list_of_card_holders):
    print(Fore.BLUE + Style.BRIGHT + "Transfer from Savings to Main Account" + Style.RESET_ALL)

    print("Choose the currency from which to transfer:")
    print("1. BGN")
    print("2. USD")
    print("3. EUR")
    print("4. Other")

    try:
        currency_choice = int(input("Enter your choice (1-4): ").strip())

        if currency_choice == 1:
            currency = 'BGN'
        elif currency_choice == 2:
            currency = 'USD'
        elif currency_choice == 3:
            currency = 'EUR'
        elif currency_choice == 4:
            currency = input("Enter the target currency (e.g., USD, EUR): ").strip().upper()
            if currency not in EXCHANGE_RATES:
                print(Fore.RED + "Invalid currency. Transfer canceled." + Style.RESET_ALL)
                return
        else:
            print(Fore.RED + "Invalid choice. Transfer canceled." + Style.RESET_ALL)
            return

        print(f"Current Savings Account Balance ({currency}): {current_user.get_savings_balance(currency)}")

        try:
            transfer_amount = float(input(f"Enter the amount to transfer from Savings to Main Account in {currency}: "))
            if transfer_amount <= 0 or transfer_amount > current_user.get_savings_balance(currency):
                print(Fore.RED + "Invalid transfer amount. Please enter a valid amount." + Style.RESET_ALL)
                return
        except ValueError:
            print(Fore.RED + "Invalid input. Please enter a valid amount." + Style.RESET_ALL)
            return

        # Update balances and transaction history based on the chosen currency
        if currency == 'BGN':
            current_user.set_balance(current_user.get_balance() + transfer_amount)
            current_user.subtract_from_savings_bgn(transfer_amount)
            current_user.add_to_history("Transfer from Savings (BGN)", transfer_amount)
        elif currency == 'USD':
            equivalent_amount_bgn = transfer_amount * EXCHANGE_RATES['USD']
            current_user.set_balance(current_user.get_balance() + equivalent_amount_bgn)
            current_user.subtract_from_savings_usd(transfer_amount)
            current_user.add_to_history("Transfer from Savings (USD)", transfer_amount)
            print(f"Equivalent amount in BGN: {equivalent_amount_bgn} BGN")
        elif currency == 'EUR':
            equivalent_amount_bgn = transfer_amount * EXCHANGE_RATES['EUR']
            current_user.set_balance(current_user.get_balance() + equivalent_amount_bgn)
            current_user.subtract_from_savings_eur(transfer_amount)
            current_user.add_to_history("Transfer from Savings (EUR)", transfer_amount)
            print(f"Equivalent amount in BGN: {equivalent_amount_bgn} BGN")
        else:
            equivalent_amount_bgn = transfer_amount * EXCHANGE_RATES[currency]
            current_user.set_balance(current_user.get_balance() + equivalent_amount_bgn)
            current_user.subtract_from_savings_bgn(transfer_amount)
            current_user.add_to_history(f"Transfer from Savings ({currency})", equivalent_amount_bgn)
            print(f"Equivalent amount in BGN: {equivalent_amount_bgn} BGN")

        # Save the updated data to the JSON file
        save_card_holders_to_json(list_of_card_holders, 'card_holders.json')

        print(Fore.GREEN + "Transfer successful!" + Style.RESET_ALL)
        print(f"Amount transferred to Main Account: {transfer_amount} {currency}")
        print(f"Main Account Balance: {current_user.get_balance()}")
        print(f"Savings Account Balance ({currency}): {current_user.get_savings_balance(currency)}")

    except ValueError:
        print(Fore.RED + "Invalid input. Transfer canceled." + Style.RESET_ALL)


def deposit_to_savings(current_user, list_of_card_holders):
    try:
        amount = float(input("Enter the amount to deposit to Savings Account (BGN): "))
        if amount <= 0:
            print(Fore.RED + "Invalid amount. Please enter a positive value." + Style.RESET_ALL)
            return
    except ValueError:
        print(Fore.RED + "Invalid input. Please enter a valid amount." + Style.RESET_ALL)
        return

    if amount > current_user.get_balance():
        print(Fore.RED + "Insufficient funds. Cannot deposit more than the available balance." + Style.RESET_ALL)
        return

    print("Do you want to deposit in another currency?")
    print("1. No (Keep the money in leva)")
    print("2. Yes (Deposit in another currency)")

    try:
        currency_choice = int(input("Enter your choice (1-2): ").strip())
        if currency_choice == 2:
            deposit_in_currency(current_user, amount, list_of_card_holders)
        elif currency_choice == 1:
            # Update balances and transaction history for leva
            current_user.subtract_from_balance(amount)
            current_user.add_to_savings_bgn(amount)
            current_user.add_to_history("Deposit to Savings (BGN)", amount)

            # Save the updated data to the JSON file
            save_card_holders_to_json(list_of_card_holders, 'card_holders.json')

            print_deposit_message("BGN", amount, amount, current_user)
        else:
            print(Fore.RED + "Invalid choice. Money will be kept in leva." + Style.RESET_ALL)

    except ValueError:
        print(Fore.RED + "Invalid input. Please enter a valid choice." + Style.RESET_ALL)



def deposit_in_currency(current_user, amount, list_of_card_holders):
    currency = input("Enter the currency (e.g., EUR, USD): ").strip().upper()

    if currency not in EXCHANGE_RATES:
        print(Fore.RED + "Invalid currency. Money will be kept in leva." + Style.RESET_ALL)
        return

    exchange_rate = EXCHANGE_RATES[currency]
    equivalent_amount_in_leva = amount * exchange_rate

    # Update balances and transaction history for the chosen currency
    if currency == 'BGN':
        current_user.set_balance(current_user.get_balance() - amount)
        current_user.add_to_savings_bgn(amount)
    elif currency == 'USD':
        current_user.set_balance(current_user.get_balance() - (amount * exchange_rate))
        current_user.add_to_savings_usd(amount)
    elif currency == 'EUR':
        current_user.set_balance(current_user.get_balance() - (amount * exchange_rate))
        current_user.add_to_savings_eur(amount)

    current_user.add_to_history(f"Deposit to Savings ({currency})", amount)

    # Save the updated data to the JSON file
    save_card_holders_to_json(list_of_card_holders, 'card_holders.json')

    print_deposit_message(currency, amount, equivalent_amount_in_leva, current_user)

def print_deposit_message(currency, deposited_amount, equivalent_amount, current_user):
    print(Fore.GREEN + "Deposit successful!" + Style.RESET_ALL)
    print(f"Deposited: {deposited_amount} {currency}")
    print(f"Equivalent amount in BGN: {equivalent_amount} BGN")
    print(f"Savings Account Balance ({currency}): {current_user.get_savings_balance(currency)} {currency}")





