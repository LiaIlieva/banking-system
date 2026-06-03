#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"
#include <vector>
#include <memory>

// Forward declaration за избягване на кръстосано рефериране (circular dependency)
class Account; 

class Customer : public Person {
private:
    std::string customerId;
    std::vector<std::shared_ptr<Account>> accounts; // Управление на паметта чрез smart pointers

public:
    Customer(const std::string& name, const std::string& email, const std::string& phone, const std::string& customerId);
    
    bool validate() const override; // Имплементация на абстрактния метод от Person
    
    std::vector<std::shared_ptr<Account>> getAccounts() const;
    void addAccount(std::shared_ptr<Account> account);
    std::string getCustomerId() const;
};

#endif // CUSTOMER_H