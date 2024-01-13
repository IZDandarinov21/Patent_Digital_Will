# saving_account_operations.py
from user_authentication import save_card_holders_to_json

EXCHANGE_RATES = {'USD': 1.79, 'EUR': 1.96}

def savings_account(current_user, list_of_card_holders):
    print("Savings Account Management")
    print("1. Transfer from Savings to Main Account")
    print("2. Deposit to Savings Account")

    try:
        choice = int(input("Enter your choice (1-2): ").strip())

        if choice == 1:
            transfer_from_savings(current_user, list_of_card_holders)
        elif choice == 2:
            deposit_to_savings(current_user, list_of_card_holders)
        else:
            print("Invalid choice. Exiting Savings Account Management.")
    except ValueError:
        print("Invalid input. Please enter a valid choice.")

def transfer_from_savings(current_user, list_of_card_holders):
    # Display the current savings balance
    print(f"Current Savings Account Balance (BGN): {current_user.get_savings_balance('BGN')}")

    try:
        transfer_amount = float(input("Enter the amount to transfer from Savings to Main Account: "))
        if transfer_amount <= 0 or transfer_amount > current_user.get_savings_balance('BGN'):
            print("Invalid transfer amount. Please enter a valid amount.")
            return
    except ValueError:
        print("Invalid input. Please enter a valid amount.")
        return

    # Update balances and transaction history
    current_user.set_balance(current_user.get_balance() + transfer_amount)
    current_user.subtract_from_savings('BGN', transfer_amount)
    current_user.add_to_history("Transfer from Savings (BGN)", transfer_amount)

    # Save the updated data to the JSON file
    save_card_holders_to_json(list_of_card_holders, 'card_holders.json')

    print("Transfer successful!")
    print(f"Amount transferred to Main Account: {transfer_amount} BGN")
    print(f"Main Account Balance: {current_user.get_balance()} BGN")
    print(f"Savings Account Balance (BGN): {current_user.get_savings_balance('BGN')}")


def deposit_to_savings(current_user, list_of_card_holders):
    try:
        amount = float(input("Enter the amount to deposit to Savings Account (BGN): "))
        if amount <= 0:
            print("Invalid amount. Please enter a positive value.")
            return
    except ValueError:
        print("Invalid input. Please enter a valid amount.")
        return

    if amount > current_user.get_balance():
        print("Insufficient funds. Cannot deposit more than the available balance.")
        return

    print("Do you want to deposit in another currency?")
    print("1. No (Keep the money in leva)")
    print("2. Yes (Deposit in another currency)")

    try:
        currency_choice = int(input("Enter your choice (1-2): ").strip())
        if currency_choice == 2:
            deposit_in_currency(current_user, amount)
        elif currency_choice == 1:
            # Update balances and transaction history for leva
            current_user.add_to_savings_bgn(amount)
            current_user.set_balance(current_user.get_balance() - amount)
            current_user.add_to_history("Deposit to Savings (BGN)", amount)

            # Save the updated data to the JSON file
            save_card_holders_to_json(list_of_card_holders, 'card_holders.json')

            print_deposit_message("BGN", amount, amount, current_user)
        else:
            print("Invalid choice. Money will be kept in leva.")

    except ValueError:
        print("Invalid input. Please enter a valid choice.")



def deposit_in_currency(current_user, amount):
    currency = input("Enter the currency (e.g., EUR, USD): ").strip().upper()

    if currency not in EXCHANGE_RATES:
        print("Invalid currency. Money will be kept in leva.")
        return

    exchange_rate = EXCHANGE_RATES[currency]
    equivalent_amount_in_leva = amount * exchange_rate

    # Update balances and transaction history for the chosen currency
    if currency == 'BGN':
        current_user.add_to_savings_bgn(amount)
    elif currency == 'USD':
        current_user.add_to_savings_usd(amount)
    elif currency == 'EUR':
        current_user.add_to_savings_eur(amount)

    current_user.set_balance(current_user.get_balance() - equivalent_amount_in_leva)
    current_user.add_to_history(f"Deposit to Savings ({currency})", amount)

    print_deposit_message(currency, amount, equivalent_amount_in_leva, current_user)

def print_deposit_message(currency, amount, equivalent_amount_in_leva, current_user):
    print(f"Deposit to Savings successful!")
    print(f"Amount deposited to Savings Account in {currency}: {amount} {currency}")
    print(f"Equivalent amount in BGN (Leva): {equivalent_amount_in_leva} BGN")
    print(f"Main Account Balance: {current_user.get_balance()} BGN")
    print(f"Savings Account Balance ({currency}): {current_user.get_savings_balance(currency)} {currency}")
    # Include similar modifications in other functions like transfer, etc.
