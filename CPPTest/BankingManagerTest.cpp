#include "BankingManager.h"

// declaration
void DumpManagerEx(const char *name, const BankingManager &mgr);
#ifndef DumpManager
#define DumpManager(x) DumpManagerEx(#x, x)
#endif
void TestBankingManager();


// implementation
void DumpManagerEx(const char *name, const BankingManager &mgr)
{
    printf("No state information for BankingManager.\n");
}

void TestBankingManager()
{
    printf("---- Test Banking Manager class\n");

    printf("Done.\n\n");
}
