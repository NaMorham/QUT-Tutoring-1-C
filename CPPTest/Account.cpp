#include "Account.h"

Account::AccountMap_t Account::ms_accounts;
double Account::ms_defaultInterestRate = 0.12; // 12%

Account *Account::Create(const uint32_t accountNum, const std::string &name, 
                                const Currency &prefCurrency, const double amountOutstanding /*= 0.0*/)
{
    AccountMap_t::const_iterator itr = ms_accounts.find(accountNum);
    if (itr != ms_accounts.end())
    {
        // account already exists
        // LOG IT
        return NULL;
    }
    if (name.empty())
    {
        // MUST have a name
        // LOG IT
        return NULL;
    }
    
    // all inputs are "valid"
    Account *newAcc = new Account(accountNum, name, prefCurrency, amountOutstanding);
    if (!newAcc)
    {
        // out of memory
        // LOG IT
        return NULL;
    }
    ms_accounts[accountNum] = newAcc;
    return newAcc;
}

bool Account::Free(Account **ppAccount)
{
    if (ppAccount && *ppAccount)
    {
        // we have a pointer, in theory it is valid
        Account *pAccount = *ppAccount;

        // remove it from the map
        AccountMap_t::iterator itr = ms_accounts.find(pAccount->GetAccountNumber());
        if (itr == ms_accounts.end())
        {
            // very bad, we have an account that is not managed
            // LOG IT
            return false;
        }
        ms_accounts.erase(itr);

        // free and clear it
        delete pAccount;
        *ppAccount = NULL;

        return true;
    }
    return false;
}

bool Account::FreeAll()  // DANGEROUS, cleans up all pointers, this would be safer with a reference counted pointer type 
{
    AccountMap_t::iterator itr = ms_accounts.begin();
    
    while (itr != ms_accounts.end())
    {
        Account *pAcc = itr->second;
        if (pAcc == NULL)
        {
            // LOG IT, but continue
            ++itr;
            continue;
        }
        itr->second = NULL;
        itr = ms_accounts.erase(itr);
        delete pAcc;
        pAcc = NULL;
    }

    return ms_accounts.empty();
}

Account::Account(const uint32_t accountNum, const std::string &name, 
                 const Currency &prefCurrency, const double amountOutstanding)
                 : m_accountNumber(accountNum), m_name(name), m_preferedCurrency(prefCurrency),
                 m_amountOutstanding(amountOutstanding), m_interestPending(0.0), m_interestRate(ms_defaultInterestRate)
{
    // nothing much to do here, in a commercial system, account creation should be logged
    // either here or in the call
}

Account::~Account()
{
    // reset everything and cleanup (since it is financial data play it safe and clean up)
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

void Account::SetAmountOwing(const double &amt)
{
    // TODO: LOG THIS!!!
    m_amountOutstanding = amt;
}

void Account::SetInterestRate(const double &rate)
{
    m_interestRate = rate;
}

// Update the amount owing by adding the specified difference
const double &Account::UpdateAmountOwing(const double &diff)
{
    // Log the change
    m_amountOutstanding += diff;
    return m_amountOutstanding;
}

const double Account::CalculateDailyInterest() const
{
    // proper interest calculation should take date and time difference into account
    // this assumes that the function is only called once a day
    double interestPerDay = m_interestRate / 365;
    double interest = ((m_amountOutstanding + m_interestPending) * interestPerDay); // One days interest
    
    return interest;
}

/* Expected to be called once per day */
const double &Account::UpdateInterestPending()
{
    m_interestPending += CalculateDailyInterest();
    return m_interestPending;
}

/* Called on the 1st of each month */
void Account::ApplyInterest()
{
    this->UpdateAmountOwing(m_interestPending);
    m_interestPending = 0;
}

// group operations
Account *Account::GetAccount(const uint32_t accNum)
{
    // easy search
    // in a real example this should call the appropriate ODBC query
    AccountMap_t::iterator itr = ms_accounts.find(accNum);

    return itr == ms_accounts.end() ? NULL : itr->second;
}

Account *Account::GetAccount(const char *name)
{
    // use the simple method - iterate
    // in a real example this should call the appropriate ODBC query
    AccountMap_t::iterator itr = ms_accounts.begin();
    for (; itr != ms_accounts.end(); ++itr)
    {
        if (itr->second && itr->second->GetName().compare(name))
        {
            return itr->second;
        }
    }
    return NULL;
}

void Account::UpdateAllInterestPending()
{
    AccountMap_t::iterator itr = ms_accounts.begin();
    for (; itr != ms_accounts.end(); ++itr)
    {
        if (itr->second) // just in case
        {
            itr->second->UpdateInterestPending();
        }
    }
}

void Account::ApplyAllInterest()
{
    AccountMap_t::iterator itr = ms_accounts.begin();
    for (; itr != ms_accounts.end(); ++itr)
    {
        if (itr->second) // just in case
        {
            itr->second->ApplyInterest();
        }
    }
}

