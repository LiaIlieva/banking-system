#ifndef TRANSFERTRANSACTION_H
#define TRANSFERTRANSACTION_H

#include "Transaction.h"

class TransferTransaction : public Transaction {
private:
    std::shared_ptr<Account> targetAccount;
    double exchangeRate;

public:
    TransferTransaction(const std::string& transactionId, double amount, std::shared_ptr<Account> sourceAccount, 
                        std::shared_ptr<Account> targetAccount, double exchangeRate = 1.0);

    void execute() override;
    void rollback() override;
    std::string getDetails() const override;
    double convertCurrency() const;
};

#endif // TRANSFERTRANSACTION_H