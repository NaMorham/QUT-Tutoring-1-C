#include "Customer.h"

#include <regex>
#include <assert.h>
#include <exception>

Customer::Customer(const std::string &name, const std::string &email, const std::string &password)
    : m_name(name), m_email(email), m_password(password)
{
    assert(name.empty() == false);
    assert(email.empty() == false);
    assert(password.empty() == false); // this may be flexible, but should never allow empty pwd

    if (!ValidateEmail(email))
    {
        throw std::invalid_argument("Invalid email");
    }

    if (!PasswordComplexityCheck(password))
    {
        throw std::invalid_argument("Password is not complex enough");
    }
}

Customer::~Customer()
{
    // invalidate the data just in case
    m_name = m_email = m_password = ""; // This really should overwrite the existing buffer first
}

void Customer::Name(const std::string &name) 
{ 
    assert(name.empty() == false); 
    m_name = name; 
}

void Customer::Password(const std::string &password) 
{ 
    assert(PasswordComplexityCheck(password)); 
    m_password = password; 
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

bool Customer::PasswordComplexityCheck(const std::string &password)
{
    return password.size() > 1;
}

// this should really return a byte array, or a base 64 encoded string, but that is up to the implementor
const std::string Customer::Encrypt(const std::string &password, const std::string &key)
{
    // we are not encrypting well
    return password;
}

const std::string Customer::Decrypt(const std::string &password, const std::string &key)
{
    // we are not encrypting well
    return password;
}
