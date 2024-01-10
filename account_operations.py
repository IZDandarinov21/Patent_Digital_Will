from user_authentication import get_user_by_names
from user_authentication import  save_card_holders_to_json
from card_Holder import Card_Holder
import random

def create_account(list_of_card_holders):
    print("Creating a new account...")

    # Generate a random card number (you may need a more sophisticated method)
    new_card_num = ''.join([str(random.randint(0, 9)) for _ in range(16)])

    # Get user information
    new_first_name = input("Enter your first name: ").strip()
    new_last_name = input("Enter your last name: ").strip()

    while True:
        try:
            new_pin = int(input("Create a 4-digit PIN: ").strip())
            if 1000 <= new_pin <= 9999:
                break
            else:
                print("Invalid PIN. Please enter a 4-digit PIN.")
        except ValueError:
            print("Invalid input. Please enter a valid PIN.")

    new_balance = 0.0  # You may set an initial balance if needed

    # Create a new Card_Holder instance
    new_card_holder = Card_Holder(new_card_num, new_pin, new_first_name, new_last_name, new_balance)

    # Add the new account to the list of cardholders
    list_of_card_holders.append(new_card_holder)

    # Save the updated list to the JSON file
    save_card_holders_to_json(list_of_card_holders, 'card_holders.json')

    print("Account created successfully!")
    print(f"Card Number: {new_card_num}")
    print(f"PIN: {new_pin}")
    print("Please remember these details for future logins.")


def close_account(current_user, card_holders_list):
    print("Closing your account...")

    # Ask the user how they want to handle the remaining balance
    print("Choose an option:")
    print("1. Withdraw the remaining balance")
    print("2. Transfer the remaining balance to another account")

    try:
        choice = int(input("Enter your choice (1-2): ").strip())

        if choice == 1:
            # Automatically withdraw all the remaining balance

            print("Warning: Choosing to withdraw will remove all of your money from your account.")
            confirm = input("Are you sure you want to proceed? (yes/no): ").strip().lower()

            if confirm == "yes":
                withdrawal_amount = current_user.get_balance()
                current_user.set_balance(0)
                current_user.add_to_history("Account Closure - Withdrawal", withdrawal_amount)
                print(f"Withdrawn {withdrawal_amount} from your account. Account closed successfully.")
            else:
                print("Withdraw canceled. Account closure canceled.")
                return

        elif choice == 2:
            print("Warning: Choosing to transfer will remove all of your money from your account.")
            confirm = input("Are you sure you want to proceed? (yes/no): ").strip().lower()

            if confirm == "yes":
                # Call the transfer_for_closing_account function to handle the transfer
                transfer_for_closing_account(current_user, card_holders_list)
            else:
                print("Transfer canceled. Account closure canceled.")
                return
        else:
            print("Invalid choice. Account closure canceled.")
            return

        # Remove the user from the list of cardholders
        card_holders_list.remove(current_user)

        # Save the updated list to the JSON file
        save_card_holders_to_json(card_holders_list, 'card_holders.json')

    except ValueError:
        print("Invalid input. Please enter a valid choice.")


def transfer_for_closing_account(sender, list_of_card_holders):
    print("Enter receiver's information:")
    receiver_first_name = input("Receiver's first name: ")
    receiver_last_name = input("Receiver's last name: ")
    receiver_card_num = input("Receiver's card number: ")

    receiver = get_user_by_names(receiver_first_name, receiver_last_name, receiver_card_num, list_of_card_holders)

    if receiver is None:
        print(f"Receiver {receiver_first_name} {receiver_last_name} not found in the list of card holders.")
        return

    # Transfer all the sender's money to the receiver
    amount = sender.get_balance()
    sender.set_balance(0)

    sender.add_to_history(f"Transfer to {receiver.get_firstName()} {receiver.get_lastName()}", amount)
    receiver_balance = receiver.get_balance()
    receiver.set_balance(receiver_balance + amount)
    receiver.add_to_history(f"Received from {sender.get_firstName()} {sender.get_lastName()}", amount)

    print("Transfer successful!")
    print(f"Sender's balance: {sender.get_balance()}")
    print(f"Receiver's balance: {receiver.get_balance()}")

    save_card_holders_to_json(list_of_card_holders, 'card_holders.json')


def change_user_info(current_user, list_of_card_holders):
    print("Select what you want to change:")
    print("1. First Name")
    print("2. Last Name")
    print("3. PIN")

    try:
        choice = int(input("Enter your choice (1-3): ").strip())

        if choice == 1:
            new_value = input("Enter your new first name: ").strip()  # Limit to 10 characters
            if len(new_value) > 10:
                print("Invalid name length. Maximum length is 10 characters. Please try again.")
                return
            current_user.set_firstName(new_value)
        elif choice == 2:
            new_value = input("Enter your new last name: ").strip()  # Limit to 10 characters
            if len(new_value) > 10:
                print("Invalid name length. Maximum length is 10 characters. Please try again.")
                return
            current_user.set_lastName(new_value)
        elif choice == 3:
            new_value = int(input("Enter your new PIN: ").strip())
            # Check if the new PIN is exactly 4 digits
            if 1000 <= new_value <= 9999:
                current_user.set_pin(new_value)
            else:
                print("Invalid PIN. Please enter a 4-digit PIN.")
                return
        else:
            print("Invalid choice. Please enter a number between 1 and 3.")
            return

        print("User information changed successfully!")

        # Save updated data to JSON file after changing user info
        save_card_holders_to_json(list_of_card_holders, 'card_holders.json')

    except ValueError:
        print("Invalid input. Please enter valid information.")