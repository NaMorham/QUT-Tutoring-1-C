
#include "BankingManager.h"

BankingManager BankingManager::ms_manager;

BankingManager::AccountList_t BankingManager::findAllAccounts() 
{ 
    AccountList_t accList;
    return accList;
}

/* find a list of all accounts for a customer */
BankingManager::AccountList_t BankingManager::findAccounts(const Customer &c) 
{ 
    AccountList_t accList;
    return accList;
}

/* find an account by name -- what should the ??? be? */
Account *BankingManager::findAccountByName(const std::string &name)
{ 
    return Account::GetAccount(name.c_str());
}

/* find an account by account number -- what should the ??? be? */
Account *BankingManager::findAccountByNumber(const uint32_t accNum) 
{ 
    return Account::GetAccount(accNum);
}

/* save an Account to the persistent store */
void persist(const Account *account) 
{ 
    printf("This is where this would be writtne to DB\n");
}

/* convert an amount from one currency to another */
const double convert(const double amount, const Currency &fromCurrency, const Currency &toCurrency) 
{ 
    double result = amount;
    printf("This is where exchange rates would be examined and used.\n");
    return result;
}
