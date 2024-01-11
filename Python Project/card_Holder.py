# card_Holder.py

class Card_Holder:
    def __init__(self, cardNum, pin, firstName, lastName, balance, savings_balance, savings_currency):
        self.cardNum = cardNum
        self.pin = pin
        self.firstName = firstName
        self.lastName = lastName
        self.balance = balance
        self.transaction_history = []
        self.investment_accounts = []
        self.savings_balance = 0.0
        self.savings_currency = "BGN"
        self.savings_balance = savings_balance
        self.savings_currency = savings_currency


    def get_cardNum(self):
        return self.cardNum

    def get_pin(self):
        return self.pin

    def get_firstName(self):
        return self.firstName

    def get_lastName(self):
        return self.lastName

    def get_balance(self):
        return self.balance

    def set_cardNum(self, newVal):
        self.cardNum = newVal

    def set_pin(self, newVal):
        self.pin = newVal

    def set_firstName(self, newVal):
        self.firstName = newVal

    def set_lastName(self, newVal):
        self.lastName = newVal

    def set_balance(self, newVal):
        self.balance = newVal

    def add_to_history(self, transaction_type, amount):
        self.transaction_history.append((transaction_type, amount))

    def get_transaction_history(self):
        return self.transaction_history

    def add_investment_account(self, investment_account):
        self.investment_accounts.append(investment_account)

    def add_to_savings(self, amount):
        self.savings_balance += amount

    def get_savings_balance(self):
        return self.savings_balance

    def get_savings_currency(self):
        return self.savings_currency

    def subtract_from_savings(self, amount):
        if amount <= self.savings_balance:
            self.savings_balance -= amount
        else:
            print("Insufficient funds in the savings account.")

