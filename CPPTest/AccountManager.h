#ifndef __AMH__ACCOUNTMANAGER_H__
#define __AMH__ACCOUNTMANAGER_H__

#include "BankingManager.h"

class AccountManager
{
public:
    AccountManager();
    ~AccountManager();

    /*A customer provides an account name and wishes to make a payment to their account. */
    const double MakePayment(const std::string &name, const double &payment);

    /* The company wants to know the balance of an account identified by account number. */
    const double GetBalance(const uint32_t accNum);

    /* The company wants to set the balance of an account identified by account number. */
    void SetBalance(const uint32_t accNum, const double balance);

private:
    BankingManager &m_manager;
};

#endif // __AMH__ACCOUNTMANAGER_H__
