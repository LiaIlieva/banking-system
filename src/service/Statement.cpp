#include "../../include/service/Statement.h"
#include "../../include/model/Account.h"
#include "../../include/model/Transaction.h"
#include <sstream>
#include <iomanip>

Statement::Statement(const std::string& statementId, std::shared_ptr<Account> account, 
                     std::chrono::system_clock::time_point startDate, std::chrono::system_clock::time_point endDate)
    : statementId(statementId), account(account), startDate(startDate), endDate(endDate) {}

void Statement::generate() {
    if (!account) return;
    
    // Изчистваме старите транзакции преди ново генериране
    transactions.clear();
    auto history = account->getTransactionHistory();
    
    // Хронологично филтриране на успешните транзакции в зададения период
    for (const auto& tx : history) {
        if (tx && tx->getTimestamp() >= startDate && tx->getTimestamp() <= endDate && tx->getStatus() == TransactionStatus::SUCCESSFUL) {
            transactions.push_back(tx);
        }
    }
}

std::string Statement::exportStatement(const std::string& format) const {
    std::stringstream ss;
    
    ss << "==================================================\n";
    ss << "             ОФИЦИАЛНО БАНКОВО ИЗВЛЕЧЕНИЕ        \n";
    ss << "==================================================\n";
    ss << "Извлечение ID: " << statementId << "\n";
    if (account) {
        ss << "Сметка №: " << account->getAccountId() << "\n";
        ss << "Текущ Баланс: " << account->getBalance() << " " << account->getCurrency() << "\n";
    }
    ss << "Формат за експорт: " << format << "\n";
    ss << "--------------------------------------------------\n";
    ss << "ДВИЖЕНИЯ ПО СМЕТКАТА ЗА ПЕРИОДА:\n";
    
    if (transactions.empty()) {
        ss << "Няма намерени успешни транзакции за избрания период.\n";
    } else {
        for (const auto& tx : transactions) {
            if (tx) {
                ss << tx->getDetails() << "\n";
            }
        }
    }
    ss << "==================================================\n";
    
    return ss.str();
}