#include "Account.h"
#include <sstream>
#include <iomanip>

// definitions

void DumpAccountEx(const char *name, const Account &acc);
#ifndef DumpAccount
#define DumpAccount(x) DumpAccountEx(#x, x)
#endif
void TestAccounts();

static void TestAccountCreateAndFree();
static void TestAccounting();

// implementation
void DumpAccountEx(const char *name, const Account &acc)
{
    std::string nm("Unknown");
    if (name && *name)
    {
        nm = name;
    }
    printf("%s: \n"
           "  Number: %12.12d\n"
           "  Name: \"%s\"\n"
           "  Currency: %d, \"%s\"\n"
           "  Outstanding Ammount: %.2lf\n"
           "  Interest Rate: %lf%%\n"
           "  Pending Interest: %.2lf\n", 
           nm.c_str(), 
           acc.GetAccountNumber(),
           acc.GetName().c_str(),
           acc.GetPreferredCurrency().Value(), acc.GetPreferredCurrency().Name().c_str(),
           acc.GetAmountOwing(),
           acc.GetInterestRate(),
           acc.GetInterestPending());

}

void TestAccounts()
{
    printf("\nTest accounts class\n-------------------\n");

    TestAccountCreateAndFree();

    TestAccounting();
}

void TestAccountCreateAndFree()
{
    printf("---- Test account creation and deleteion\n");

    printf("-- Check map is empty. ");
    assert(Account::GetNumAccounts() == 0);
    printf("[OK]\n");

    Account *pA1 = NULL;
    // attempt to create an account using new
    // pA1 = new Account(0, "bob", Currency::AUD, 0.0); // expect compilation error

    printf("-- Create an account. ");
    pA1 = Account::Create(1, "bob", Currency::CAD, 0.0);
    assert(pA1 != NULL);
    printf("[OK]\n");
    DumpAccount(*pA1);

    printf("-- Check map size == 1. ");
    assert(Account::GetNumAccounts() == 1);
    printf("[OK]\n");

    printf("-- Attempt to create an account with a duplicate number. ");
    Account *pA2 = Account::Create(1, "charlie", Currency::GBP, 10.0);
    assert(pA2 == NULL);
    printf("[OK]\n");

    printf("-- Check map size still == 1. ");
    assert(Account::GetNumAccounts() == 1);
    printf("[OK]\n");

    printf("-- Create an account with duplicate details but different number. ");
    pA2 = Account::Create(2, "bob", Currency::CAD, 0.0);
    assert(pA2 != NULL);
    printf("[OK]\n");
    DumpAccount(*pA2);

    printf("-- Check map size == 2. ");
    assert(Account::GetNumAccounts() == 2);
    printf("[OK]\n");

    const int sz = 10;
    printf("-- Create %d extra accounts with duplicate details but different number: \n", sz);
    Account **pA3 = new Account*[sz];
    for (int i = 0; i < sz; ++i)
    {
        std::stringstream ss;
        ss << "John Doe #" << i+1;
        Account *pTmp = Account::Create(3 + i, ss.str().c_str(), Currency::USD, 42.42);
        assert(pTmp != NULL);
        pA3[i] = pTmp;
        pTmp = NULL;
        DumpAccount(*pA3[i]);
    }

    printf("-- Check map size == %d. ", sz + 2);
    assert(Account::GetNumAccounts() == (sz + 2));
    printf("[OK]\n");

    printf("-- Delete an account #2. \n");
    printf("     Delete account. ");
    assert(Account::Free(&pA2) == true);
    printf("[OK]\n");
    printf("     Check pointer is null. ");
    assert(pA2 == NULL);
    printf("[OK]\n");

    printf("-- Check map size == %d. ", sz + 1);
    assert(Account::GetNumAccounts() == (sz + 1));
    printf("[OK]\n");

    printf("-- Attempt to delete a null account. ");
    assert(Account::Free(&pA2) == false);
    printf("[OK]\n");

    printf("-- Check map size still == %d. ", sz + 1);
    assert(Account::GetNumAccounts() == (sz + 1));
    printf("[OK]\n");

    // cleanup
    Account::Free(&pA1);
    for (int i = 0; i < sz; ++i)
    {
        Account *pTmp = pA3[i];
        Account::Free(&pTmp);
        pA3[i] = NULL;
    }

    printf("-- Check map size == 0. ");
    assert(Account::GetNumAccounts() == 0);
    printf("[OK]\n");

    printf("DONE.\n\n");
}

void TestAccounting()
{
    // create dummy accounts
    printf("---- Test account accounting operations\n");

    printf("-- Check map is empty. ");
    assert(Account::GetNumAccounts() == 0);
    printf("[OK]\n");

    const int sz = 20;
    int i = 0;

    for (i = 0; i < sz; ++i)
    {
        std::stringstream ss;
        ss << "Testuser #" << std::setw(2) << std::setfill('0') << i+1;
        assert(Account::Create(i + 1, ss.str(), Currency(i % Currency::XEU + 1), 1000.00) != NULL);
    }

    printf("-- Check map is correct size == %d. ", sz);
    assert(Account::GetNumAccounts() == sz);
    printf("[OK]\n");

    // cleanup
    printf("-- Cleanup\n");
    assert(Account::FreeAll() == true);

    printf("-- Check map size == 0. ");
    assert(Account::GetNumAccounts() == 0);
    printf("[OK]\n");

    printf("DONE.\n\n");
}
