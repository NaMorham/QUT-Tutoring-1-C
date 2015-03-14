#ifndef __AMH__USERBASE_H__
#define __AMH__USERBASE_H__

#include <string>
#include <assert.h>
#include <exception>

class UserBase
{
public:
    UserBase(const std::string &name, const std::string &email, const std::string &password)
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
    virtual ~UserBase()
    {
        // invalidate the data just in case
        m_name = m_email = m_password = ""; // This really should overwrite the existing buffer first
    }

    inline const std::string &Name() const { return m_name; }
    inline const std::string &Email() const { return m_email; }
    inline const std::string &Password() const { return m_password; } // dangerous, assuing password is clear text

    void Name(const std::string &name) { assert(name.empty() == false); m_name = name; }
    void Password(const std::string &password) { assert(password.empty() == false); m_password = password; }

    // utility functions
    virtual bool ValidateEmail(const std::string &email) = 0;
    virtual bool PasswordComplexityCheck(const std::string &password) = 0;
    // this should really return a byte array, or a base 64 encoded string, but that is up to the implementor
    virtual const std::string Encrypt(const std::string &password, const std::string &key) = 0;
    virtual const std::string Decrypt(const std::string &password, const std::string &key) = 0;

protected:
    std::string m_name;
    std::string m_email;
    std::string m_password;
};

#endif // __AMH__USERBASE_H__
