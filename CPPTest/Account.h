#ifndef __AMH__ACCOUNT_H__
#define __AMH__ACCOUNT_H__

#include <string>
#include <vector>
#include "Currency.h"

class Account
{
private:
    std::string m_name;
    std::string m_accountNumber;
    Currency m_preferedCurrency;
    double m_ammountOutstanding;    // This is not safe to use for normal financial calculations
};

#endif
