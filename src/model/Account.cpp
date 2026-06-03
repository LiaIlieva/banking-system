#include "../../include/model/Account.h"
#include "../../include/model/Customer.h"
#include "../../include/model/Transaction.h"
#include <stdexcept>

Account::Account(const std::string& accountId, double initialBalance, const std::string& currency, 
                 AccountStatus status, std::shared_ptr<Customer> owner)
    : accountId(accountId), balance(initialBalance), currency(currency), status(status), owner(owner) {}

double Account::getBalance() const {
    return balance;
}

void Account::setBalance(double amount) {
    balance = amount;
}

std::string Account::getAccountId() const {
    return accountId;
}

std::string Account::getCurrency() const {
    return currency;
}

AccountStatus Account::getStatus() const {
    return status;
}

void Account::setStatus(AccountStatus newStatus) {
    status = newStatus;
}

std::shared_ptr<Customer> Account::getOwner() const {
    return owner.lock(); // Трансформира weak_ptr в shared_ptr за безопасна работа
}

void Account::deposit(double amount) {
    if (status != AccountStatus::ACTIVE) {
        throw std::runtime_error("Сметката не е активна. Депозитът е отказан.");
    }
    if (amount <= 0) {
        throw std::invalid_argument("Сумата за депозит трябва да бъде положителна.");
    }
    balance += amount;
}

void Account::addTransactionToHistory(std::shared_ptr<Transaction> transaction) {
    if (transaction) {
        transactionHistory.push_back(transaction);
    }
}

std::vector<std::shared_ptr<Transaction>> Account::getTransactionHistory() const {
    return transactionHistory;
}