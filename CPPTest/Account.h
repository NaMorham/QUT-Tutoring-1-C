#ifndef __AMH__ACCOUNT_H__
#define __AMH__ACCOUNT_H__

#include <string>
#include <map>
#include <stdint.h>
#include <assert.h>

#include "Currency.h"

class Account
{
public:
    typedef std::map<uint32_t, Account *> AccountMap_t;

    enum eTaskTypes
    {
        ATT_CALCULATE_INTEREST,
        ATT_APPLY_INTEREST,
        ATT_NOTIFY_MANAGERS
    };

    /** 
        Create a new account
        returns null if account num is in use or name is empty
    */
    static Account *Create(const uint32_t accountNum, const std::string &name, const Currency &prefCurrency, const double amountOutstanding = 0.0);
    static bool Free(Account **ppAccount);
    static bool FreeAll();  // DANGEROUS, cleans up all pointers, this would be safer with a reference counted pointer type 

    inline const uint32_t GetAccountNumber() const { return m_accountNumber; }
    inline const std::string &GetName() const { return m_name; }
    inline const Currency &GetPreferredCurrency() const { return m_preferedCurrency; }
    inline const double &GetAmountOwing() const { return m_amountOutstanding; }
    inline const double &GetInterestPending() const { return m_interestPending; }
    inline const double GetTotalOwing() const { return m_amountOutstanding + m_interestPending; }
    inline const double &GetInterestRate() const { return m_interestRate; }

    void SetName(const std::string &name);
    void SetCurrency(const Currency &currency);
    // NOTE: Cannot change account number
    void SetAmountOwing(const double &ammt);
    void SetInterestRate(const double &rate);

    // Update the amount owing by adding the specified difference
    const double &UpdateAmountOwing(const double &diff);
    const double CalculateDailyInterest() const; // Calculate the amount of interest for 1 day
    
    /* Expected to be called once per day */
    const double &UpdateInterestPending();  // Update pending interest amount with calculated interest
    /* Called on the 1st of each month */
    void ApplyInterest();

    // Operations on account map
    static const size_t GetNumAccounts() { return ms_accounts.size(); }
    static const AccountMap_t &GetAccountMap() { return ms_accounts; }
    static Account *GetAccount(const uint32_t accNum);
    static Account *GetAccount(const char *name);
    static void UpdateAllInterestPending();
    static void ApplyAllInterest();

private:
    Account(const uint32_t accountNum, const std::string &name, 
            const Currency &prefCurrency, const double amountOutstanding);
    ~Account();

    uint32_t m_accountNumber;       // Primary key, must be unique
    std::string m_name;
    Currency m_preferedCurrency;
    double m_amountOutstanding;    // This is not safe to use for normal financial calculations
                                    // rounding issues with floating point calculations may cause
                                    // issues.
    double m_interestPending;
    double m_interestRate;

    // Management and handling of accounts
    static AccountMap_t ms_accounts;
    static double ms_defaultInterestRate;

    // NO COPYING OF ACCOUNTS
    Account(const Account &original) { assert("Attempt to call copy constructor on an Account object" == NULL);  }
    const Account &operator=(const Account &rhs) { assert("Attempt to call copy constructor on an Account object" == NULL); return *this; }
};

#endif
