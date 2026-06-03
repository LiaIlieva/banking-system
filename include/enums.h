#ifndef ENUMS_H
#define ENUMS_H

enum class AccountStatus {
    ACTIVE,
    INACTIVE,
    SUSPENDED
};

enum class InterestPeriod {
    MONTHLY,
    ANNUALLY
};

enum class TransactionStatus {
    PENDING,
    SUCCESSFUL,
    FAILED,
    ROLLED_BACK
};

#endif // ENUMS_H