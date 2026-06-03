#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "Account.h"

class CheckingAccount : public Account {
private:
    double overdraftLimit;

public:
    CheckingAccount(const std::string& accountId, double initialBalance, const std::string& currency, 
                    AccountStatus status, std::shared_ptr<Customer> owner, double overdraftLimit);

    void withdraw(double amount) override; // Имплементация съобразена с овърдрафта
    double getAvailableBalance() const;
    double getOverdraftLimit() const;
};

#endif // CHECKINGACCOUNT_H