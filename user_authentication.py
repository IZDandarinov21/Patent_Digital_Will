# user_authentication.py

from card_Holder import Card_Holder

def authenticate_user():
    list_of_card_holders = [
        Card_Holder("127631386428723472989", 1232, "John", "Petterson", 150.31),
        Card_Holder("885493957439598989345", 4354, "Max", "Ovley", 546.21),
        Card_Holder("989549443243424324767", 8773, "Anakin", "Jeferson", 89.43),
        Card_Holder("329392934920194839238", 9731, "Anna", "Karalian", 234.67),
        Card_Holder("124214273889959040032", 2289, "Dawn", "Smith", 743.56)
    ]

    while True:
        try:
            debit_card_num = input("Please insert your debit card: ")
            debit_match = [holder for holder in list_of_card_holders if holder.cardNum == debit_card_num]
            if len(debit_match) > 0:
                return debit_match[0]
            else:
                print("Card number not recognized. Please try again.")
        except:
            print("Card number not recognized. Please try again.")

def get_user_pin(current_user):
    while True:
        try:
            user_pin = int(input("Please enter your pin: ").strip())
            if current_user.get_pin() == user_pin:
                return True
            else:
                print("Invalid PIN. Please try again.")
        except:
            print("Invalid PIN. Please try again.")
