#include "../../include/model/SavingsAccount.h"
#include <stdexcept>

SavingsAccount::SavingsAccount(const std::string& accountId, double initialBalance, const std::string& currency, 
                               AccountStatus status, std::shared_ptr<Customer> owner, double interestRate, InterestPeriod period)
    : Account(accountId, initialBalance, currency, status, owner), interestRate(interestRate), interestPeriod(period) {}

void SavingsAccount::withdraw(double amount) {
    if (getStatus() != AccountStatus::ACTIVE) {
        throw std::runtime_error("Сметката не е активна. Тегленето е отказано.");
    }
    if (amount <= 0) {
        throw std::invalid_argument("Сумата за теглене трябва да бъде положителна.");
    }
    
    // Спестовната сметка няма право на овърдрафт
    if (getBalance() < amount) {
        throw std::runtime_error("Недостатъчна наличност по спестовната сметка.");
    }
    
    setBalance(getBalance() - amount);
}
void SavingsAccount::applyInterestAmount(double amount) {
    if (getStatus() != AccountStatus::ACTIVE) {
        throw std::runtime_error("Сметката не е активна. Начисляването е отказано.");
    }
    if (amount < 0) {
        throw std::invalid_argument("Лихвата не може да бъде отрицателна сума.");
    }
    
    // Записваме промяната в баланса чрез protected метода
    setBalance(getBalance() + amount); 
}

double SavingsAccount::getInterestRate() const {
    return interestRate;
}

InterestPeriod SavingsAccount::getInterestPeriod() const {
    return interestPeriod;
}