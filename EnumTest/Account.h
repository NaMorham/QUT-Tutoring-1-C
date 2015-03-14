#ifndef __AMH__ACCOUNT_H__
#define __AMH__ACCOUNT_H__

#include "CurrencyData.h"
#include "Customer.h"

#include <stdint.h>

class Account
{
public:
    Account(Customer *pCustomer, const std::string &accNo,
			Currency::CurrencyData *pCurrency, const int64_t outstandingAmt = 0LL);
    ~Account();

private:
    // this can be replaced by a list if there are more than one customers associated with an account
    Customer *m_pCustomer; 
    std::string m_accountNumber;
    Currency::CurrencyData *m_pCurrency;
    // in Java this is better represented as a BigInteger, but we will assume accounts 
    // with resonably small amounts stored
    int64_t m_outstandingAmount;    // in 1/1 000 000 of a cent
};

#endif // __AMH__ACCOUNT_H__
