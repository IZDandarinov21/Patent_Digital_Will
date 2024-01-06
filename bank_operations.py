# bank_operations.py
from user_authentication import get_user_by_names
from card_Holder import Card_Holder
def print_menu():
    print("Please choose from one of the following options...")
    print("1. Deposit")
    print("2. Withdrawal")
    print("3. Show balance")
    print("4. Transfer")
    print("5. Exit")

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


def transfer(current_user):
    list_of_card_holders = [
        Card_Holder("127631386428723472989", 1232, "Atanas", "Apostolov", 150.31),
        Card_Holder("885493957439598989345", 4354, "Ivaila", "Kuzmova", 546.21),
        Card_Holder("989549443243424324767", 8773, "Anakin", "Jeferson", 89.43),
        Card_Holder("329392934920194839238", 9731, "Anna", "Karalian", 234.67),
        Card_Holder("124214273889959040032", 2289, "Dawn", "Smith", 743.56)
    ]

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





