#ifndef WITHDRAWALTRANSACTION_H
#define WITHDRAWALTRANSACTION_H

#include "Transaction.h"

class WithdrawalTransaction : public Transaction {
private:
    std::string channel; // Напр. ATM, POS, Counter

public:
    WithdrawalTransaction(const std::string& transactionId, double amount, 
                          std::shared_ptr<Account> account, const std::string& channel);

    void execute() override;
    void rollback() override;
    std::string getDetails() const override;
};

#endif // WITHDRAWALTRANSACTION_H