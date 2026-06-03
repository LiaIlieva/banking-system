#include "../../include/model/TransferTransaction.h"
#include "../../include/model/Account.h"

TransferTransaction::TransferTransaction(const std::string& transactionId, double amount, std::shared_ptr<Account> sourceAccount, 
                                         std::shared_ptr<Account> targetAccount, double exchangeRate)
    : Transaction(transactionId, amount, sourceAccount), targetAccount(targetAccount), exchangeRate(exchangeRate) {}

double TransferTransaction::convertCurrency() const {
    return getAmount() * exchangeRate;
}

void TransferTransaction::execute() {
    auto sourceAcc = getAccount();
    if (!sourceAcc || !targetAccount) {
        setStatus(TransactionStatus::FAILED);
        return;
    }

    try {
        // 1. Теглене от изходната сметка
        sourceAcc->withdraw(getAmount());
        
        // 2. Депозиране в целевата сметка (с преизчислена валута)
        double finalAmount = convertCurrency();
        targetAccount->deposit(finalAmount);
        
        setStatus(TransactionStatus::SUCCESSFUL);
        
        // Записваме транзакцията в хронологията и на двете сметки
        auto sharedThis = std::shared_ptr<Transaction>(this, [](Transaction*){});
        sourceAcc->addTransactionToHistory(sharedThis);
        targetAccount->addTransactionToHistory(sharedThis);
        
    } catch (...) {
        // Ако нещо се провали по време на стъпките, транзакцията маркираме като провалена
        setStatus(TransactionStatus::FAILED);
    }
}

void TransferTransaction::rollback() {
    auto sourceAcc = getAccount();
    if (getStatus() == TransactionStatus::SUCCESSFUL && sourceAcc && targetAccount) {
        try {
            targetAccount->withdraw(convertCurrency());
            sourceAcc->deposit(getAmount());
            setStatus(TransactionStatus::ROLLED_BACK);
        } catch (...) {
            // Критична грешка при rollback
        }
    }
}

std::string TransferTransaction::getDetails() const {
    return "[БАНКОВ ПРЕВОД] " + Transaction::getDetails() + 
           " -> Получател: " + (targetAccount ? targetAccount->getAccountId() : "Няма") + 
           " | Курс: " + std::to_string(exchangeRate);
}