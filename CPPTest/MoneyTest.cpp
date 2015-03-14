#include "Money.h"
#include <assert.h>

void DumpMoneyEx(const char *name, const Money &mny);
#ifndef DumpMoney
#define DumpMoney(x) DumpMoneyEx(#x, x)
#endif
void TestMoneyClass();

extern long GetMillionthVal(const char *str);
void ValTest();


// implementation

void DumpMoneyEx(const char *name, const Money &mny)
{
    std::string nm("Unknown");
    if (name && *name)
    {
        nm = name;
    }
    long w = mny.GetWholeAmmount();
    long p = mny.GetPartAmmount();
    printf("%-3.3s: \"%5.5s [%12.12s]\", %4.4d, %8.8d, %12.12lld\n", nm.c_str(), mny.ToString().c_str(),
        mny.ToStringFull().c_str(), w, p, mny.GetRawAmmount());
}

void TestMoneyClass()
{
    printf("\n\nTest Money Class\n----------------\n");

    printf("Test Construction\n");
    Money m1;
    DumpMoney(m1);
    assert(m1.GetRawAmmount() == 0L);

    Money m2(123000000);    // $1.23
    DumpMoney(m2);
    assert(m2.GetRawAmmount() == 123000000);

    Money m3(4, 56);        // $4.56
    DumpMoney(m3);
    assert(m3.GetRawAmmount() == 456000000);

    Money m4("7.89");       // $7.89
    DumpMoney(m4);
    assert(m4.GetRawAmmount() == 789000000);

    Money m5(".1230000000");// 12.3c
    DumpMoney(m5);
    assert(m5.GetRawAmmount() == 12300000);

    Money m6("15");         // $15.00
    DumpMoney(m6);
    assert(m6.GetRawAmmount() == 1500000000);

    Money m7(1, 100);       // $1 + 100c
    DumpMoney(m7);
    assert(m7.GetRawAmmount() == 200000000);

    Money m8(123600000);    // $1, 23.6c
    DumpMoney(m8);
    assert(m8.GetRawAmmount() == 123600000);

    Money m9(m2);
    DumpMoney(m9);
    assert(m9.GetRawAmmount() == 123000000);

    // Rounding
    long result = 0;
    result = Money::RoundEven(m1.GetPartAmmount());
    assert(result == 0L);
    assert(m1.ToString().compare("0.00") == 0);

    result = Money::RoundEven(m2.GetPartAmmount());
    assert(result == 23000000);
    assert(m2.ToString().compare("1.23") == 0);

    result = Money::RoundEven(m8.GetPartAmmount());
    assert(result == 24000000);
    assert(m8.ToString().compare("1.24") == 0);

    // Compare values
    assert(m2 == m9);
    assert(m1 != m9);

    // Arithmatic on values
}

void ValTest()
{
    long val = long(pow(10L, 3L));

    GetMillionthVal(".123");
    GetMillionthVal(".1230000000000");
    GetMillionthVal(".456007");
    GetMillionthVal(".123456789");
}
