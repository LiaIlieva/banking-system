#include "../../include/model/CheckingAccount.h"
#include <stdexcept>

CheckingAccount::CheckingAccount(const std::string& accountId, double initialBalance, const std::string& currency, 
                                 AccountStatus status, std::shared_ptr<Customer> owner, double overdraftLimit)
    : Account(accountId, initialBalance, currency, status, owner), overdraftLimit(overdraftLimit) {}

void CheckingAccount::withdraw(double amount) {
    if (getStatus() != AccountStatus::ACTIVE) {
        throw std::runtime_error("Сметката не е активна. Тегленето е отказано.");
    }
    if (amount <= 0) {
        throw std::invalid_argument("Сумата за теглене трябва да бъде положителна.");
    }
    
    // Валидация спрямо овърдрафт лимита
    if (getBalance() + overdraftLimit < amount) {
        throw std::runtime_error("Недостатъчна наличност (надвишен овърдрафт лимит).");
    }
    
    setBalance(getBalance() - amount);
}

double CheckingAccount::getAvailableBalance() const {
    return getBalance() + overdraftLimit;
}

double CheckingAccount::getOverdraftLimit() const {
    return overdraftLimit;
}