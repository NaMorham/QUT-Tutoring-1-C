#ifndef __AMH__CUSTOMER_H__
#define __AMH__CUSTOMER_H__

#include "CurrencyData.h"

class Customer
{
public:
    Customer(const std::string &name, const std::string &email,
        const std::string &password);
    ~Customer();

    static bool ValidateEmail(const std::string &email);

private:

    std::string m_name;
    std::string m_email;
    std::string m_password;
};

#endif // __AMH__CUSTOMER_H__
