#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>
#include <vector>
#include <memory>
#include <chrono>

// Forward declarations
class Account;
class Transaction;

class Statement {
private:
    std::string statementId;
    std::shared_ptr<Account> account;
    std::chrono::system_clock::time_point startDate;
    std::chrono::system_clock::time_point endDate;
    std::vector<std::shared_ptr<Transaction>> transactions;

public:
    Statement(const std::string& statementId, std::shared_ptr<Account> account, 
              std::chrono::system_clock::time_point startDate, std::chrono::system_clock::time_point endDate);

    void generate();
    // За улеснение връщаме std::string като симулация на файл в конзолата
    std::string exportStatement(const std::string& format) const; 
};

#endif // STATEMENT_H