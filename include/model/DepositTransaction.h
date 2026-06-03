#ifndef DEPOSITTRANSACTION_H
#define DEPOSITTRANSACTION_H

#include "Transaction.h"

class DepositTransaction : public Transaction {
private:
    std::string source; // Напр. ATM, На каса, Банков превод

public:
    DepositTransaction(const std::string& transactionId, double amount, 
                       std::shared_ptr<Account> account, const std::string& source);

    void execute() override;
    void rollback() override;
    std::string getDetails() const override;
};

#endif // DEPOSITTRANSACTION_H