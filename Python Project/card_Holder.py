# card_Holder.py

class Card_Holder:
    def __init__(self, card_Num, pin, firstName, lastName, balance,
                 savings_balance_bgn, savings_currency_bgn,
                 savings_balance_usd, savings_currency_usd,
                 savings_balance_eur, savings_currency_eur):
        self.cardNum = card_Num
        self.pin = pin
        self.firstName = firstName
        self.lastName = lastName
        self.balance = balance
        self.transaction_history = []
        self.investment_accounts = []
        self.savings_balance_bgn = savings_balance_bgn

        # Set default value for savings_currency_bgn if not provided
        self.savings_currency_bgn = savings_currency_bgn if savings_currency_bgn else "BGN"

        self.savings_balance_usd = savings_balance_usd
        self.savings_currency_usd = savings_currency_usd
        self.savings_balance_eur = savings_balance_eur
        self.savings_currency_eur = savings_currency_eur

        # Set default values for currency fields if not provided
        if not self.savings_currency_usd:
            self.savings_currency_usd = "USD"
        if not self.savings_currency_eur:
            self.savings_currency_eur = "EUR"




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

    def add_to_savings_bgn(self, amount):
        self.savings_balance_bgn += amount

    def get_savings_balance_bgn(self):
        return self.savings_balance_bgn

    def get_savings_currency_bgn(self):
        return self.savings_currency_bgn

    def subtract_from_savings_bgn(self, amount):
        if amount <= self.savings_balance_bgn:
            self.savings_balance_bgn -= amount
        else:
            print("Insufficient funds in the savings account.")

    def add_to_savings_usd(self, amount):
        self.savings_balance_usd += amount

    def get_savings_balance_usd(self):
        return self.savings_balance_usd

    def get_savings_currency_usd(self):
        return self.savings_currency_usd

    def subtract_from_savings_usd(self, amount):
        if amount <= self.savings_balance_usd:
            self.savings_balance_usd -= amount
        else:
            print("Insufficient funds in the USD savings account.")

    def add_to_savings_eur(self, amount):
        self.savings_balance_eur += amount

    def get_savings_balance_eur(self):
        return self.savings_balance_eur

    def get_savings_currency_eur(self):
        return self.savings_currency_eur

    def subtract_from_savings_eur(self, amount):
        if amount <= self.savings_balance_eur:
            self.savings_balance_eur -= amount
        else:
            print("Insufficient funds in the Euro savings account.")

    def get_savings_balance(self, currency):
        if currency == 'BGN':
            return self.savings_balance_bgn
        elif currency == 'USD':
            return self.savings_balance_usd
        elif currency == 'EUR':
            return self.savings_balance_eur
        else:
            print(f"Invalid currency: {currency}")
            return 0.0

