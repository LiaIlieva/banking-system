#include "../../include/model/DepositTransaction.h"
#include "../../include/model/Account.h"

DepositTransaction::DepositTransaction(const std::string& transactionId, double amount, 
                                       std::shared_ptr<Account> account, const std::string& source)
    : Transaction(transactionId, amount, account), source(source) {}

void DepositTransaction::execute() {
    try {
        if (getAccount()) {
            getAccount()->deposit(getAmount());
            setStatus(TransactionStatus::SUCCESSFUL);
            getAccount()->addTransactionToHistory(std::shared_ptr<Transaction>(this, [](Transaction*){})); 
            // Бележка: Използва се къстъм деструктор, тъй като обектът се управлява извън хронологията
        } else {
            setStatus(TransactionStatus::FAILED);
        }
    } catch (...) {
        setStatus(TransactionStatus::FAILED);
    }
}

void DepositTransaction::rollback() {
    if (getStatus() == TransactionStatus::SUCCESSFUL && getAccount()) {
        getAccount()->withdraw(getAmount()); // Обратна операция
        setStatus(TransactionStatus::ROLLED_BACK);
    }
}

std::string DepositTransaction::getDetails() const {
    return "[ДЕПОЗИТ] " + Transaction::getDetails() + " | Източник: " + source;
}