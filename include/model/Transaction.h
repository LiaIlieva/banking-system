#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <chrono>
#include <memory>
#include "../enums.h"

class Account; // Forward declaration

class Transaction {
private:
    std::string transactionId; // Private (Решение 3)
    double amount;
    std::chrono::system_clock::time_point timestamp;
    TransactionStatus status;
    std::shared_ptr<Account> account;

protected:
    void setStatus(TransactionStatus newStatus);

public:
    Transaction(const std::string& transactionId, double amount, std::shared_ptr<Account> account);
    virtual ~Transaction() = default;

    virtual void execute() = 0;   // Полиморфизъм (Решение 1)
    virtual void rollback() = 0;  // Полиморфизъм (Решение 1)
    virtual std::string getDetails() const;

    std::string getTransactionId() const;
    double getAmount() const;
    TransactionStatus getStatus() const;
    std::shared_ptr<Account> getAccount() const;
    std::chrono::system_clock::time_point getTimestamp() const;
};

#endif // TRANSACTION_H