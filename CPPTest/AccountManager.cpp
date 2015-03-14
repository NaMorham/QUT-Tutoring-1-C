#include "AccountManager.h"
#include <exception>
#include <stdexcept>

AccountManager::AccountManager()
    : m_manager(BankingManager::GetManager()) {}

AccountManager::~AccountManager() {}

/*A customer provides an account name and wishes to make a payment to their account. */
const double AccountManager::MakePayment(const std::string &name, const double &payment)
{
    double newBalance = 0.0;
    Account *pAccount = m_manager.findAccountByName(name);
    if (!name.empty() && pAccount)
    {
        newBalance = pAccount->UpdateAmountOwing(-payment);
    }
    else
    {
        // LOG IT - Account could not be found
        std::string err = "Account name \"";
        err += name;
        err += "\" not found.";
        throw std::invalid_argument(err);
    }
    return newBalance;
}

/* The company wants to know the balance of an account identified by account number. */
const double AccountManager::GetBalance(const uint32_t accNum)
{
    Account *pAccount = m_manager.findAccountByNumber(accNum);
    if (pAccount)
    {
        return pAccount->GetAmountOwing();
    }
    else
    {
        // LOG IT - Account could not be found
        std::string err = "Could not find account";
        throw std::invalid_argument(err);
    }
    return 0.0; // should not get here
}

/* The company wants to set the balance of an account identified by account number. */
void AccountManager::SetBalance(const uint32_t accNum, const double balance)
{
    Account *pAccount = m_manager.findAccountByNumber(accNum);
    if (pAccount)
    {
        pAccount->SetAmountOwing(balance);
    }
    else
    {
        // LOG IT - Account could not be found
        std::string err = "Could not find account";
        throw std::invalid_argument(err);
    }
}
