# bank_operations.py

from user_authentication import get_user_by_names
from user_authentication import  save_card_holders_to_json


def deposit(card_holder, list_of_card_holders):
    try:
        deposit_amount = float(input("How much do you like to deposit: "))
        card_holder.set_balance(card_holder.get_balance() + deposit_amount)
        card_holder.add_to_history("Deposit", deposit_amount)
        print("Thank you for your money, your balance is: ", str(card_holder.get_balance()))

        # Save updated data to JSON file after deposit
        save_card_holders_to_json(list_of_card_holders, 'card_holders.json')

    except ValueError:
        print("Invalid input")


def withdrawal(card_holder, list_of_card_holders):
    try:
        withdrawal_amount = float(input("How much do you like to withdrawal: "))
        if card_holder.get_balance() < withdrawal_amount:
            print("Insufficient balance :(")
        else:
            card_holder.set_balance(card_holder.get_balance() - withdrawal_amount)
            card_holder.add_to_history("Withdrawal", withdrawal_amount)
            print("You're good to go! Thank you :) Your balance is: ", str(card_holder.get_balance()))

            # Save updated data to JSON file after withdrawal
            save_card_holders_to_json(list_of_card_holders, 'card_holders.json')

    except ValueError:
        print("Invalid input")


def check_balance_and_transaction_history(card_holder):
    print("Your current balance is: ", card_holder.get_balance())
    print("Deposit History: ")
    for transaction in card_holder.get_transaction_history():
        if transaction[0] == "Deposit":
            print(transaction)
    print("\nWithdrawal History: ")
    for transaction in card_holder.get_transaction_history():
        if transaction[0] == "Withdrawal":
            print(transaction)


def transfer(current_user, list_of_card_holders):
    print("Enter sender's information:")
    sender_first_name = input("Sender's first name: ")
    sender_last_name = input("Sender's last name: ")
    sender_card_num = input("Sender's card number: ")

    sender = get_user_by_names(sender_first_name, sender_last_name, sender_card_num, list_of_card_holders)

    if sender is None:
        print(f"Sender {sender_first_name} {sender_last_name} not found in the list of card holders.")
        return

    print("Enter receiver's information:")
    receiver_first_name = input("Receiver's first name: ")
    receiver_last_name = input("Receiver's last name: ")
    receiver_card_num = input("Receiver's card number: ")

    receiver = get_user_by_names(receiver_first_name, receiver_last_name, receiver_card_num, list_of_card_holders)

    if receiver is None:
        print(f"Receiver {receiver_first_name} {receiver_last_name} not found in the list of card holders.")
        return

    while True:
        try:
            amount = float(input("Enter the amount to be sent: "))
            break
        except ValueError:
            print("Invalid input. Please enter a valid amount.")

    sender_balance = sender.get_balance()

    if sender_balance < amount:
        print("Insufficient balance. Transaction canceled.")
        return

    sender.set_balance(sender_balance - amount)
    sender.add_to_history(f"Transfer to {receiver.get_firstName()} {receiver.get_lastName()}", amount)

    receiver_balance = receiver.get_balance()
    receiver.set_balance(receiver_balance + amount)
    receiver.add_to_history(f"Received from {sender.get_firstName()} {sender.get_lastName()}", amount)

    print("Transfer successful!")
    print(f"Sender's balance: {sender.get_balance()}")
    print(f"Receiver's balance: {receiver.get_balance()}")

    # Save updated data to JSON file when modifying something
    save_card_holders_to_json(list_of_card_holders, 'card_holders.json')


def pay_basic_expenses(current_user, list_of_card_holders):
    print("Paying Basic Living Expenses...")

    expense_options = {
        1: ("Water Bill", "water", 50.0),
        2: ("Electricity Bill", "electricity", 100.0),
        3: ("Internet Bill", "internet", 30.0),
        4: ("Tax Bills", "tax", 400.0),
        5: ("Pay all taxes", "all", 580) # Adding a default value for tax
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
                    print("Insufficient balance. Tax payment canceled.")
                    return

                print(f"{tax_name} payment of {tax_amount} BGN confirmed!")

                # Deduct the amount from the user's balance
                current_user.set_balance(current_user.get_balance() - tax_amount)
                current_user.add_to_history(f"Tax Payment - {tax_name}", tax_amount)

                print("Payment successful!")
                print(f"Remaining balance: {current_user.get_balance()} BGN")

                # Save updated data to JSON file after tax payment
                save_card_holders_to_json(list_of_card_holders, 'card_holders.json')

            else:
                print("Invalid tax choice. Tax payment canceled.")
                return

        elif choice in expense_options:
            expense_name, expense_code, expense_amount = expense_options[choice]

            # Check if the user has sufficient balance
            if current_user.get_balance() < expense_amount:
                print("Insufficient balance. Bill payment canceled.")
                return

            print(f"{expense_name} payment of {expense_amount} BGN confirmed!")

            # Deduct the amount from the user's balance
            current_user.set_balance(current_user.get_balance() - expense_amount)
            current_user.add_to_history(f"Bill Payment - {expense_name}", expense_amount)

            print("Payment successful!")
            print(f"Remaining balance: {current_user.get_balance()} BGN")

            # Save updated data to JSON file after bill payment
            save_card_holders_to_json(list_of_card_holders, 'card_holders.json')

        else:
            print("Invalid choice. Bill payment canceled.")

    except ValueError:
        print("Invalid input. Please enter a valid choice.")













