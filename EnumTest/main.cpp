#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Account.h"

int main(int argc, char *argv[])
{
    printf("AUD = %s\n", Currency::AUD.Name().c_str());

    assert(Customer::ValidateEmail("test@hotmail.com") == true);
    assert(Customer::ValidateEmail("test.2@hotmail.com") == true);
    assert(Customer::ValidateEmail("test.2__AT__hotmail.com") == false);

    return 0;
}
