
#include <stdio.h>
#include <stdlib.h>

#include "Currency.h"

#ifdef USE_SAFE_MONEY_TYPE
#include "Money.h"
extern void TestMoneyClass();
extern void ValTest();
#else
static void TestMoneyClass() {}
static void ValTest() {}
#endif

extern void TestEnumClass();
extern void TestAccounts();
extern void TestBankingManager();

int main(int argc, char *argv[])
{
    printf("\n\nDEBUG: CPP Test\n");

    TestMoneyClass();

    TestEnumClass();

    ValTest();

    TestAccounts();

    TestBankingManager();

    return 0;
}
