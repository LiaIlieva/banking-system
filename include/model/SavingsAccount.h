#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account {
private:
    double interestRate;
    InterestPeriod interestPeriod;

public:
    SavingsAccount(const std::string& accountId, double initialBalance, const std::string& currency, 
                   AccountStatus status, std::shared_ptr<Customer> owner, double interestRate, InterestPeriod period);

    void withdraw(double amount) override; // Имплементация (напр. без право на надвишаване на баланса)
    
    double calculateInterest() const;
    void applyInterest();

    double getInterestRate() const;
    InterestPeriod getInterestPeriod() const;
};

#endif // SAVINGSACCOUNT_H