#ifndef INTERESTCALCULATOR_H
#define INTERESTCALCULATOR_H

#include "../enums.h"
#include <memory>

class SavingsAccount; // Зависимост само от спестовни сметки (Решение 4)

class InterestCalculator {
private:
    double rate;
    InterestPeriod period;

public:
    InterestCalculator(double rate, InterestPeriod period);

    double calculate(std::shared_ptr<SavingsAccount> account) const;
    void apply(std::shared_ptr<SavingsAccount> account);
};

#endif // INTERESTCALCULATOR_H