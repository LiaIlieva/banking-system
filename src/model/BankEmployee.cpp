#include "../../include/model/BankEmployee.h"
#include "../../include/model/Transaction.h"

BankEmployee::BankEmployee(const std::string& name, const std::string& email, const std::string& phone, 
                           const std::string& employeeId, const std::string& role)
    : Person(name, email, phone), employeeId(employeeId), role(role) {}

bool BankEmployee::validate() const {
    return !name.empty() && !employeeId.empty() && !role.empty();
}

bool BankEmployee::approveTransaction(std::shared_ptr<Transaction> t) {
    if (!t || t->getStatus() != TransactionStatus::PENDING) {
        return false;
    }
    // Служителят одобрява транзакцията и я задейства
    t->execute();
    return t->getStatus() == TransactionStatus::SUCCESSFUL;
}

std::string BankEmployee::getEmployeeId() const {
    return employeeId;
}

std::string BankEmployee::getRole() const {
    return role;
}