#include "../../include/model/Customer.h"
#include "../../include/model/Account.h"

Customer::Customer(const std::string& name, const std::string& email, const std::string& phone, const std::string& customerId)
    : Person(name, email, phone), customerId(customerId) {}

bool Customer::validate() const {
    // Базова валидация: проверка за празни полета и коректен формат на ID
    return !name.empty() && !customerId.empty() && email.find('@') != std::string::npos;
}

std::vector<std::shared_ptr<Account>> Customer::getAccounts() const {
    return accounts;
}

void Customer::addAccount(std::shared_ptr<Account> account) {
    if (account) {
        accounts.push_back(account);
    }
}

std::string Customer::getCustomerId() const {
    return customerId;
}