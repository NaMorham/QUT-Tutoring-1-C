#include "Account.h"
#include <regex>

Account::Account(Customer *pCustomer, const std::string &accNo,
                 Currency::CurrencyData *pCurrency, const int64_t outstandingAmt /*= 0LL*/)
				 : m_pCustomer(pCustomer), m_accountNumber(accNo), 
				   m_pCurrency(pCurrency), m_outstandingAmount(outstandingAmt)
{
}


Account::~Account()
{
}
