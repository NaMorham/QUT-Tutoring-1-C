#include <assert.h>
#include <exception>

#include "Currency.h"

// declarations

void DumpCurrencyEx(const char *name, const Currency &mny);
#ifndef DumpCurrency
#define DumpCurrency(x) DumpCurrencyEx(#x, x)
#endif
void TestEnumClass();


// implementation
void DumpCurrencyEx(const char *name, const Currency &cur)
{
    std::string nm("Unknown");
    if (name && *name)
    {
        nm = name;
    }
    printf("%s: %d: \"%s\"\n", nm.c_str(), cur.Value(), cur.Name().c_str());
}

void TestEnumClass()
{
    printf("\n\n");

    Currency cur = Currency::AUD;
    cur = Currency::GBP;

    Currency cur2 = Currency::AUD;

    assert(cur2 < cur);

    for (int i = Currency::AUD; i <= Currency::XEU; ++i)
    {
        DumpCurrency(i);
    }

    try
    {
        Currency cBad(42);
    }
    catch (std::out_of_range &e)
    {
        printf("Out of Range exception caught: %s\n", e.what()); // expected
    }
    catch (...)
    {
        printf("ERROR: Unhandled exceptiion thrown.\n");
    }
}
