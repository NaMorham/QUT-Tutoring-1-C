#ifndef __AMH__BANKINGMANAGER_H__
#define __AMH__BANKINGMANAGER_H__

#include "Account.h"
#include "Customer.h"
#include <list>

class BankingManager
{
public:
    typedef std::list<Account *> AccountList_t;

    /* find a list of all accounts */
    AccountList_t findAllAccounts();

    /* find a list of all accounts for a customer */
    AccountList_t findAccounts(const Customer &c);

    /* find an account by name -- what should the ??? be? */
    Account *findAccountByName(const std::string &name);

    /* find an account by account number -- what should the ??? be? */
    Account *findAccountByNumber(const uint32_t accNum);

    /* save an Account to the persistent store */
    void persist(const Account *account);

    /* convert an amount from one currency to another */
    const double convert(const double amount, const Currency &fromCurrency, const Currency &toCurrency);

    static BankingManager &GetManager() { return ms_manager; }

private:
    static BankingManager ms_manager;

    BankingManager() {}
    ~BankingManager() {}
};

#endif // __AMH__BANKINGMANAGER_H__
