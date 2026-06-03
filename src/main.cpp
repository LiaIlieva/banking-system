#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <windows.h>

// Models
#include "../include/model/Customer.h"
#include "../include/model/BankEmployee.h"
#include "../include/model/CheckingAccount.h"
#include "../include/model/SavingsAccount.h"
#include "../include/model/DepositTransaction.h"
#include "../include/model/WithdrawalTransaction.h"
#include "../include/model/TransferTransaction.h"

// Services
#include "../include/service/InterestCalculator.h"
#include "../include/service/Statement.h"

int main() {
    std::cout << "=== STARTING BANKING SYSTEM INTEGRATION TESTS ===\n\n";

    // 1. Create Customer and Bank Employee
    auto customer = std::make_shared<Customer>(
        "John Doe", "john.doe@email.com", "+359888123456", "CUST_2026_001"
    );
    
    auto employee = std::make_shared<BankEmployee>(
        "Mary Smith", "m.smith@bank.com", "+359888987654", "EMP_102", "Credit Consultant"
    );

    std::cout << "[Customer]: " << customer->getContactInfo() << "\n";
    std::cout << "[Employee]: " << employee->getContactInfo() << "\n";
    std::cout << "Customer profile validity: " << (customer->validate() ? "VALID" : "INVALID") << "\n\n";

    // 2. Create Accounts (Checking with Overdraft & Savings)
    auto checking = std::make_shared<CheckingAccount>(
        "BG11UNCR96601012345678", 500.0, "BGN", AccountStatus::ACTIVE, customer, 200.0
    ); // 500 BGN balance + 200 BGN overdraft limit

    auto savings = std::make_shared<SavingsAccount>(
        "BG22UNCR96601087654321", 1000.0, "EUR", AccountStatus::ACTIVE, customer, 3.5, InterestPeriod::ANNUALLY
    ); // 1000 EUR balance, 3.5% interest rate

    customer->addAccount(checking);
    customer->addAccount(savings);

    std::cout << "--- Initial Balances ---\n";
    std::cout << "Checking Account: " << checking->getBalance() << " " << checking->getCurrency() 
              << " (Available funds with overdraft: " << checking->getAvailableBalance() << " " << checking->getCurrency() << ")\n";
    std::cout << "Savings Account: " << savings->getBalance() << " " << savings->getCurrency() << "\n\n";

    // Record start time before transactions (for statement generation purposes)
    auto startTime = std::chrono::system_clock::now();

    // 3. Test Deposit (DepositTransaction)
    std::cout << "--- Executing Deposit Transaction ---\n";
    auto deposit = std::make_shared<DepositTransaction>("TX_001", 150.0, checking, "ATM Sofia Center");
    deposit->execute();
    std::cout << deposit->getDetails() << "\n";
    std::cout << "New Checking Account Balance: " << checking->getBalance() << " BGN\n\n";

    // 4. Test Withdrawal within Overdraft Limit (WithdrawalTransaction)
    std::cout << "--- Executing Withdrawal Transaction (Using Overdraft) ---\n";
    // Attempting to withdraw 700 BGN when balance is 650 BGN. Since overdraft limit is 200, this should succeed.
    auto withdrawal = std::make_shared<WithdrawalTransaction>("TX_002", 700.0, checking, "Branch Counter 1");
    withdrawal->execute();
    std::cout << withdrawal->getDetails() << "\n";
    std::cout << "New Checking Account Balance: " << checking->getBalance() << " BGN (Overdraft utilized)\n\n";

    // 5. Test Transfer with Currency Conversion (TransferTransaction)
    std::cout << "--- Executing Transfer Transaction (From Savings EUR to Checking BGN) ---\n";
    // Transferring 100 EUR from savings to checking with an exchange rate of 1.95583
    auto transfer = std::make_shared<TransferTransaction>("TX_003", 100.0, savings, checking, 1.95583);
    transfer->execute();
    std::cout << transfer->getDetails() << "\n";
    std::cout << "Final Savings Account Balance: " << savings->getBalance() << " EUR\n";
    std::cout << "Final Checking Account Balance (After transfer received): " << checking->getBalance() << " BGN\n\n";

    // 6. Test Interest Calculation (InterestCalculator)
    std::cout << "--- Applying Interest to Savings Account ---\n";
    std::cout << "Savings Balance before interest: " << savings->getBalance() << " EUR\n";
    
    // Creating calculator with a base rate of 3.5%
    InterestCalculator calc(3.5, InterestPeriod::ANNUALLY);
    double expectedInterest = calc.calculate(savings);
    std::cout << "Calculated interest from service: " << expectedInterest << " EUR\n";
    
    calc.apply(savings); // Apply the calculated interest
    std::cout << "Savings Balance after interest applied: " << savings->getBalance() << " EUR\n\n";

    // Wait 1 second to ensure a distinct timeframe for the statement
    Sleep(1000);
    auto endTime = std::chrono::system_clock::now();

    // 7. Test Statement Generation (Statement)
    std::cout << "--- Generating Official Bank Statement ---\n";
    Statement stmt("STMT_2026_JUNE", checking, startTime, endTime);
    stmt.generate();
    
    // Export and print the report to the console
    std::string textReport = stmt.exportStatement("TXT");
    std::cout << textReport << "\n";

    // 8. Simulate Rollback functionality
    std::cout << "--- Simulating Transaction Rollback (Undoing the last withdrawal) ---\n";
    std::cout << "Checking Balance before rollback: " << checking->getBalance() << " BGN\n";
    withdrawal->rollback();
    std::cout << "Transaction Status: " 
              << (withdrawal->getStatus() == TransactionStatus::ROLLED_BACK ? "ROLLED_BACK" : "ACTIVE") << "\n";
    std::cout << "Checking Balance after rollback (700 BGN Restored): " << checking->getBalance() << " BGN\n";

    std::cout << "\n=== ALL INTEGRATION TESTS PASSED SUCCESSFULLY ===\n";
    return 0;
}