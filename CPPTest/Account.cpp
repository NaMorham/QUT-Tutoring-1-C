#include "Account.h"

Account::AccountMap_t Account::ms_accounts;
double Account::ms_defaultInterestRate = 0.12; // 12%

Account *Account::CreateAccount(const uint32_t accountNum, const std::string &name, 
                                const Currency &prefCurrency, const double amountOutstanding /*= 0.0*/)
{
    return NULL;
}
bool Account::FreeAccount(Account **ppAccount)
{
    return false;
}

Account::Account(const uint32_t accountNum, const std::string &name, 
                 const Currency &prefCurrency, const double amountOutstanding)
                 : m_accountNumber(accountNum), m_name(name), m_preferedCurrency(prefCurrency),
                 m_amountOutstanding(amountOutstanding), m_interestPending(0.0), m_interestRate(ms_defaultInterestRate)
{
    // 
}

Account::~Account()
{
    // reset everything and cleanup
    m_accountNumber = 0;
    m_name = "";
    m_preferedCurrency = Currency::AUD;
    m_amountOutstanding = 0.0;
    m_interestPending = 0.0;
    m_interestRate = ms_defaultInterestRate;
}

void Account::SetName(const std::string &name)
{
    if (name.empty())
    {
        throw std::invalid_argument("Empty name passed as Account Name");
    }
    m_name = name;
}

void Account::SetCurrency(const Currency &currency)
{
    // TODO: Perform conversion on amount owing and pending interest
    m_preferedCurrency = currency;
}

void Account::SetamountOwing(const double &amt)
{
    // TODO: LOG THIS!!!
    m_amountOutstanding = amt;
}

// Update the amount owing by adding the specified difference
const double &Account::UpdateAmountOwing(const double &diff)
{
    m_amountOutstanding += diff;
    return m_amountOutstanding;
}

const double Account::CalculateInterest() const
{
    // proper interest calculation should take date and time difference into account
    // this assumes that the function is only called once a day
    double interestPerDay = m_interestRate / 365;
    double interest = ((m_amountOutstanding + m_interestPending) * interestPerDay);
    
    return interest;
}

const double &Account::UpdateInterestPending()
{
    m_interestPending += CalculateInterest();
    return m_interestPending;
}
