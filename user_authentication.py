# user_authentication.py

import json
from card_Holder import Card_Holder


def authenticate_user(card_holders_list):
    while True:
        try:
            debit_card_num = input("Please insert your debit card number: ")

            matched_users = [holder for holder in card_holders_list if
                             holder.get_cardNum() == debit_card_num]

            if len(matched_users) > 0:
                return matched_users[0]
            else:
                print("Invalid card number or PIN. Please try again.")
        except ValueError:
            print("Invalid input. Please enter a valid card number and PIN.")
        except IndexError:
            print("Invalid card number or PIN. Please try again.")

# ...

def load_card_holders_from_json(filename):
    try:
        with open(filename, 'r') as file:
            card_holders_data = json.load(file)
            card_holders = [
                Card_Holder(
                    data['cardNum'],
                    data['pin'],
                    data['firstName'],
                    data['lastName'],
                    data['balance']
                )
                for data in card_holders_data
            ]
            return card_holders
    except (FileNotFoundError, json.JSONDecodeError):
        return []

def save_card_holders_to_json(card_holders, filename):
    card_holders_data = [
        {
            'cardNum': holder.get_cardNum(),
            'pin': holder.get_pin(),
            'firstName': holder.get_firstName(),
            'lastName': holder.get_lastName(),
            'balance': holder.get_balance()
        }
        for holder in card_holders
    ]
    with open(filename, 'w') as file:
        json.dump(card_holders_data, file, indent=2)

def get_user_pin(current_user):
    while True:
        try:
            user_pin = int(input("Please enter your PIN: ").strip())
            if current_user.get_pin() == user_pin:
                return True
            else:
                print("Invalid PIN. Please try again.")
        except:
            print("Invalid PIN. Please try again.")

def get_user_by_names(first_name, last_name, card_number, card_holders_list):
    for holder in card_holders_list:
        print(f"Checking {holder.get_firstName()} {holder.get_lastName()} with card number {holder.get_cardNum()}")
        if (
            holder.get_firstName().lower() == first_name.lower()
            and holder.get_lastName().lower() == last_name.lower()
            and holder.get_cardNum() == card_number
        ):
            print("Match found!")
            return holder

    print("No match found.")
    return None