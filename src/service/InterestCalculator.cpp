#include "../../include/service/InterestCalculator.h"
#include "../../include/model/SavingsAccount.h"

InterestCalculator::InterestCalculator(double rate, InterestPeriod period)
    : rate(rate), period(period) {}

double InterestCalculator::calculate(std::shared_ptr<SavingsAccount> account) const {
    if (!account) return 0.0;
    
    // Използваме лихвения процент, дефиниран в самата сметка!
    double accountRate = account->getInterestRate(); 
    
    // Тук може да се добави по-сложна логика спрямо периода (MONTHLY/ANNUALLY),
    // но ето базовото изчисление:
    return account->getBalance() * (accountRate / 100.0);
}

void InterestCalculator::apply(std::shared_ptr<SavingsAccount> account) {
    if (!account || account->getStatus() != AccountStatus::ACTIVE) return;
    
    // 1. Изчисляваме лихвата тук
    double interest = calculate(account);
    
    // 2. Подаваме ВЕЧЕ ИЗЧИСЛЕНАТА сума на сметката
    account->applyInterestAmount(interest); 
}