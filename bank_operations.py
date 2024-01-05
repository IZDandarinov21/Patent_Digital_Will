# bank_operations.py

from card_Holder import Card_Holder

def print_menu():
    print("Please choose from one of the following options...")
    print("1. Deposit")
    print("2. Withdrawal")
    print("3. Show balance")
    print("4. Exit")

def deposit(card_holder):
    try:
        deposit_amount = float(input("How much do you like to deposit: "))
        card_holder.set_balance(card_holder.get_balance() + deposit_amount)
        card_holder.add_to_history("Deposit", deposit_amount)
        print("Thank you for your money. Your balance is: ", str(card_holder.get_balance()))
    except:
        print("Invalid input")

def withdrawal(card_holder):
    try:
        withdrawal_amount = float(input("How much do you like to withdrawal: "))
        if card_holder.get_balance() < withdrawal_amount:
            print("Insufficient balance :(")
        else:
            card_holder.set_balance(card_holder.get_balance() - withdrawal_amount)
            card_holder.add_to_history("Withdrawal", withdrawal_amount)
            print("You're good to go! Thank you :)")
    except:
        print("Invalid input")

def check_balance(card_holder):
    print("Your current balance is: ", card_holder.get_balance())
    print("Deposit History: ")
    for transaction in card_holder.get_transaction_history():
        if transaction[0] == "Deposit":
            print(transaction)
    print("\nWithdrawal History: ")
    for transaction in card_holder.get_transaction_history():
        if transaction[0] == "Withdrawal":
            print(transaction)
