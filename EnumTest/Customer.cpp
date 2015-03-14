#include "Customer.h"
#include <regex>

Customer::Customer(const std::string &name, const std::string &email,
                 const std::string &password)
: m_name(name), m_email(email), m_password(password)
{
}


Customer::~Customer()
{
}

bool Customer::ValidateEmail(const std::string &email)
{
    // proper validation should be more thorough, and not assume ascii
    std::regex email_regex("[a-zA-Z0-9/.-_]+@[a-zA-Z0-9/.-_]+", std::regex_constants::ECMAScript);
    if (std::regex_search(email, email_regex)) 
    {
        return true;
    }
    else
    {
        // return information on the failure
        return false;
    }
}
