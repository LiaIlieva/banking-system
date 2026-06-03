#ifndef BANKEMPLOYEE_H
#define BANKEMPLOYEE_H

#include "Person.h"
#include <memory>

class Transaction; // Forward declaration

class BankEmployee : public Person {
private:
    std::string employeeId;
    std::string role;

public:
    BankEmployee(const std::string& name, const std::string& email, const std::string& phone, 
                 const std::string& employeeId, const std::string& role);

    bool validate() const override;
    bool approveTransaction(std::shared_ptr<Transaction> t);
    
    std::string getEmployeeId() const;
    std::string getRole() const;
};

#endif // BANKEMPLOYEE_H