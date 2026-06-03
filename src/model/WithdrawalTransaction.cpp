#include "../../include/model/WithdrawalTransaction.h"
#include "../../include/model/Account.h"

WithdrawalTransaction::WithdrawalTransaction(const std::string& transactionId, double amount, 
                                             std::shared_ptr<Account> account, const std::string& channel)
    : Transaction(transactionId, amount, account), channel(channel) {}

void WithdrawalTransaction::execute() {
    try {
        if (getAccount()) {
            getAccount()->withdraw(getAmount());
            setStatus(TransactionStatus::SUCCESSFUL);
            getAccount()->addTransactionToHistory(std::shared_ptr<Transaction>(this, [](Transaction*){}));
        } else {
            setStatus(TransactionStatus::FAILED);
        }
    } catch (...) {
        setStatus(TransactionStatus::FAILED);
    }
}

void WithdrawalTransaction::rollback() {
    if (getStatus() == TransactionStatus::SUCCESSFUL && getAccount()) {
        getAccount()->deposit(getAmount()); // Връщане на парите
        setStatus(TransactionStatus::ROLLED_BACK);
    }
}

std::string WithdrawalTransaction::getDetails() const {
    return "[ТЕГЛЕНЕ] " + Transaction::getDetails() + " | Канал: " + channel;
}