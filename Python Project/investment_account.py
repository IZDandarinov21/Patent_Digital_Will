class InvestmentAccount:
    def __init__(self, investment_type, initial_investment):
        self.investment_type = investment_type
        self.initial_investment = initial_investment
        self.current_value = initial_investment
        self.investment_history = []

    def add_to_history(self, action, amount):
        self.investment_history.append((action, amount))

    def get_investment_type(self):
        return self.investment_type

    def get_initial_investment(self):
        return self.initial_investment

    def get_current_value(self):
        return self.current_value

    def get_investment_history(self):
        return self.investment_history