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

    // Пренаписване на метода за теглене
    void withdraw(double amount) override; 
    
    // Новият метод, който приема вече изчислената от калкулатора сума
    void applyInterestAmount(double amount);

    double getInterestRate() const;
    InterestPeriod getInterestPeriod() const;
};

#endif // SAVINGSACCOUNT_H