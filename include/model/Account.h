#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <memory>
#include "../enums.h"

// Forward declarations
class Customer;
class Transaction;

class Account {
private:
    std::string accountId;
    double balance; // Private от съображения за сигурност (Решение 3)
    std::string currency;
    AccountStatus status;
    std::weak_ptr<Customer> owner; // weak_ptr предотвратява cyclic dependency (Customer <-> Account)
    std::vector<std::shared_ptr<Transaction>> transactionHistory;

protected:
    // Позволява на наследниците директно да променят баланса при транзакции
    void setBalance(double amount); 

public:
    Account(const std::string& accountId, double initialBalance, const std::string& currency, 
            AccountStatus status, std::shared_ptr<Customer> owner);
    virtual ~Account() = default;

    double getBalance() const;
    std::string getAccountId() const;
    std::string getCurrency() const;
    AccountStatus getStatus() const;
    void setStatus(AccountStatus newStatus);
    std::shared_ptr<Customer> getOwner() const;

    // Виртуални методи за транзакциите
    virtual void deposit(double amount);
    virtual void withdraw(double amount) = 0; // Чисто виртуален метод (сериозна валидация в наследниците)
    
    void addTransactionToHistory(std::shared_ptr<Transaction> transaction);
    std::vector<std::shared_ptr<Transaction>> getTransactionHistory() const;
};

#endif // ACCOUNT_H