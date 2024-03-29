# user_authentication.py
import json
from colorama import Fore, Style
from card_Holder import Card_Holder


def authenticate_user(card_holders_list):
    print(Fore.GREEN + Style.BRIGHT + """
    ************************************
            Debit Card Authentication
    ************************************
    """ + Style.RESET_ALL)

    while True:
        try:
            debit_card_num = input("Please insert your debit card number: ")

            matched_users = [holder for holder in card_holders_list if
                             holder.get_cardNum() == debit_card_num]

            if len(matched_users) > 0:
                return matched_users[0]
            else:
                print(Fore.RED + "Invalid card number or PIN. Please try again." + Style.RESET_ALL)
        except ValueError:
            print(Fore.RED + "Invalid input. Please enter a valid card number and PIN." + Style.RESET_ALL)
        except IndexError:
            print(Fore.RED + "Invalid card number or PIN. Please try again." + Style.RESET_ALL)




def load_card_holders_from_json(filename):
    try:
        with open(filename, 'r') as file:
            card_holders_data = json.load(file)
            card_holders = [
                Card_Holder(
                    data.get('spending_account', {}).get('cardNum', ''),
                    data.get('spending_account', {}).get('pin', ''),
                    data.get('spending_account', {}).get('firstName', ''),
                    data.get('spending_account', {}).get('lastName', ''),
                    data.get('spending_account', {}).get('balance', 0.0),
                    data.get('savings_account', {}).get('balance_bgn', 0.0),
                    data.get('savings_account', {}).get('currency_bgn', ''),
                    data.get('savings_account', {}).get('balance_usd', 0.0),
                    data.get('savings_account', {}).get('currency_usd', ''),
                    data.get('savings_account', {}).get('balance_eur', 0.0),
                    data.get('savings_account', {}).get('currency_eur', ''),
                )
                for data in card_holders_data
            ]
            return card_holders
    except (FileNotFoundError, json.JSONDecodeError):
        return []


def save_card_holders_to_json(card_holders, filename):
    card_holders_data = [
        {
            'spending_account': {
                'cardNum': holder.get_cardNum(),
                'pin': holder.get_pin(),
                'firstName': holder.get_firstName(),
                'lastName': holder.get_lastName(),
                'balance': round(holder.get_balance(), 2),
            },
            'savings_account': {
                'balance_bgn': round(holder.get_savings_balance_bgn(), 2),
                'currency_bgn': holder.get_savings_currency_bgn(),
                'balance_usd': round(holder.get_savings_balance_usd(), 2),
                'currency_usd': holder.get_savings_currency_usd(),
                'balance_eur': round(holder.get_savings_balance_eur(), 2),
                'currency_eur': holder.get_savings_currency_eur(),
            }
        }
        for holder in card_holders
    ]
    with open(filename, 'w') as file:
        json.dump(card_holders_data, file, indent=2)



def get_user_pin(current_user):
    print(Fore.GREEN + Style.BRIGHT + """
    ************************************
            User PIN Verification
    ************************************
    """ + Style.RESET_ALL)

    while True:
        try:
            user_pin = int(input("Please enter your PIN: ").strip())
            if current_user.get_pin() == user_pin:
                return True
            else:
                print(Fore.RED + "Invalid PIN. Please try again." + Style.RESET_ALL)
        except ValueError:
            print(Fore.RED + "Invalid PIN. Please try again." + Style.RESET_ALL)



def get_user_by_names(first_name, last_name, card_number, card_holders_list):


    for holder in card_holders_list:
        if (
            holder.get_firstName().lower() == first_name.lower()
            and holder.get_lastName().lower() == last_name.lower()
            and holder.get_cardNum() == card_number
        ):
            print(Fore.GREEN + "Match found!" + Style.RESET_ALL)
            return holder

    print(Fore.RED + "No match found." + Style.RESET_ALL)
    return None


