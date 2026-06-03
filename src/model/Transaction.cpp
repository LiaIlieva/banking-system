#include "../../include/model/Transaction.h"
#include "../../include/model/Account.h"
#include <sstream>
#include <iomanip>

Transaction::Transaction(const std::string& transactionId, double amount, std::shared_ptr<Account> account)
    : transactionId(transactionId), amount(amount), timestamp(std::chrono::system_clock::now()), 
      status(TransactionStatus::PENDING), account(account) {}

void Transaction::setStatus(TransactionStatus newStatus) {
    status = newStatus;
}

std::string Transaction::getTransactionId() const {
    return transactionId;
}

double Transaction::getAmount() const {
    return amount;
}

TransactionStatus Transaction::getStatus() const {
    return status;
}

std::shared_ptr<Account> Transaction::getAccount() const {
    return account;
}

std::chrono::system_clock::time_point Transaction::getTimestamp() const {
    return timestamp;
}

std::string Transaction::getDetails() const {
    std::time_t time = std::chrono::system_clock::to_time_t(timestamp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    
    return "ID: " + transactionId + " | Сума: " + std::to_string(amount) + 
           " | Дата: " + ss.str() + " | Сметка: " + (account ? account->getAccountId() : "Няма");
}