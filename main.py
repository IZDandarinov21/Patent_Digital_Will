# main.py

from bank_operations import print_menu, deposit, withdrawal, check_balance
from cardHolder import CardHolder

if __name__ == "__main__":
    current_user = CardHolder("", "", "", "", "")

    list_of_card_holders = [
        CardHolder("127631386428723472989", 1232, "John", "Petterson", 150.31),
        CardHolder("885493957439598989345", 4354, "Max", "Ovley", 546.21),
        CardHolder("989549443243424324767", 8773, "Anakin", "Jeferson", 89.43),
        CardHolder("329392934920194839238", 9731, "Anna", "Karalian", 234.67),
        CardHolder("124214273889959040032", 2289, "Dawn", "Smith", 743.56)
    ]

    debit_card_num = " "
    while True:
        try:
            debit_card_num = input("Please insert your debit card: ")
            debit_match = [holder for holder in list_of_card_holders if holder.cardNum == debit_card_num]
            if len(debit_match) > 0:
                current_user = debit_match[0]
                break
            else:
                print("Card number not recognized. Please try again.")
        except:
            print("Card number not recognized. Please try again.")

    while True:
        try:
            user_pin = int(input("Please enter your pin: ").strip())
            if current_user.get_pin() == user_pin:
                break
            else:
                print("Invalid PIN. Please try again.")
        except:
            print("Invalid PIN. Please try again.")

    print("Welcome ", current_user.get_firstName(), " :)")

    option = 0
    while True:
        print_menu()
        try:
            option = int(input())
        except:
            print("Invalid input. Please try again. ")
        if option == 1:
            deposit(current_user)
        elif option == 2:
            withdrawal(current_user)
        elif option == 3:
            check_balance(current_user)
        elif option == 4:
            break
        else:
            option = 0

    print("Thank you. Have a nice day :)")
