#ifndef __AMH__CUSTOMER_H__
#define __AMH__CUSTOMER_H__

#include <string>


class Customer 
{
    Customer(const std::string &name, const std::string &email, const std::string &password);
    virtual ~Customer();

    inline const std::string &Name() const { return m_name; }
    inline const std::string &Email() const { return m_email; }
    inline const std::string &Password() const { return m_password; } // dangerous, if password is in memory as clear text

    void Name(const std::string &name);
    void Password(const std::string &password);

    // utility functions
    static bool ValidateEmail(const std::string &email);
    static bool PasswordComplexityCheck(const std::string &password);
    // this should really return a byte array, or a base 64 encoded string, but that is up to the implementor
    static const std::string Encrypt(const std::string &password, const std::string &key);
    static const std::string Decrypt(const std::string &password, const std::string &key);

private:
    std::string m_name;
    std::string m_email;
    std::string m_password;
};

#endif // __AMH__CUSTOMER_H__
