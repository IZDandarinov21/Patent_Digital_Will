from user_authentication import  save_card_holders_to_json

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
    print(f"Current Savings Account Balance: {current_user.get_savings_balance()} BGN")

    try:
        transfer_amount = float(input("Enter the amount to transfer from Savings to Main Account: "))
        if transfer_amount <= 0 or transfer_amount > current_user.get_savings_balance():
            print("Invalid transfer amount. Please enter a valid amount.")
            return
    except ValueError:
        print("Invalid input. Please enter a valid amount.")
        return

    # Update balances and transaction history
    current_user.set_balance(current_user.get_balance() + transfer_amount)
    current_user.subtract_from_savings(transfer_amount)
    current_user.add_to_history("Transfer from Savings", transfer_amount)

    # Save the updated data to the JSON file
    save_card_holders_to_json(list_of_card_holders, 'card_holders.json')

    print("Transfer successful!")
    print(f"Amount transferred to Main Account: {transfer_amount} BGN")
    print(f"Main Account Balance: {current_user.get_balance()} BGN")
    print(f"Savings Account Balance: {current_user.get_savings_balance()} BGN")




def deposit_to_savings(current_user, list_of_card_holders):
    try:
        amount = float(input("Enter the amount to deposit to Savings Account: "))
        if amount <= 0:
            print("Invalid amount. Please enter a positive value.")
            return
    except ValueError:
        print("Invalid input. Please enter a valid amount.")
        return

    # Check if there is enough balance in the main account
    if current_user.get_balance() < amount:
        print("Insufficient main account balance. Deposit to Savings canceled.")
        return

    # Update balances and transaction history
    current_user.add_to_savings(amount)
    current_user.set_balance(current_user.get_balance() - amount)
    current_user.add_to_history("Deposit to Savings", amount)

    # Save the updated data to the JSON file
    save_card_holders_to_json(list_of_card_holders, 'card_holders.json')

    print("Deposit to Savings successful!")
    print(f"Amount deposited to Savings Account: {amount} BGN")
    print(f"Main Account Balance: {current_user.get_balance()} BGN")
    print(f"Savings Account Balance: {current_user.get_savings_balance()} BGN")


