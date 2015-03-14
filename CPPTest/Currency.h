#ifndef __AMH__CURRENCY_H__
#define __AMH__CURRENCY_H__

#include <string>
#include <vector>
#include <assert.h>

class Currency;

class CurrencyData
{
public:
    const std::string &Name() const { return m_name;  }
    const int Value() const { return m_value; }

    operator const std::string() const { return Name(); }
    operator const int() const { return Value(); }

    const bool operator<(const int rhs) const;
    const bool operator<(const CurrencyData &rhs) const;
    const bool operator<=(const int rhs) const;
    const bool operator<=(const CurrencyData &rhs) const;
    const bool operator==(const int rhs) const;
    const bool operator==(const CurrencyData &rhs) const;
    const bool operator>(const int rhs) const;
    const bool operator>(const CurrencyData &rhs) const;
    const bool operator>=(const int rhs) const;
    const bool operator>=(const CurrencyData &rhs) const;
    const bool operator!=(const int rhs) const;
    const bool operator!=(const CurrencyData &rhs) const;

private:
    friend class Currency;

    CurrencyData(const std::string &name);
    ~CurrencyData();

    std::string m_name;
    int m_value;

    static int ms_val; // the "value of the enum"
    static std::vector<CurrencyData *> ms_data;
    static const CurrencyData *Find(const int value);

    // NOT ALLOWED TO COPY
    CurrencyData(const CurrencyData &orig) : m_value(0), m_name("BAD") { assert(false);  }
    const CurrencyData &operator=(const CurrencyData &rhs) { assert(false); return *this; }
};

class Currency
{
public:
    static const CurrencyData AUD;
    static const CurrencyData CAD;
    static const CurrencyData GBP;
    static const CurrencyData JPY;
    static const CurrencyData USD;
    static const CurrencyData XEU;

    Currency();
    Currency(const CurrencyData &cd);
    Currency(const Currency &orig);
    Currency(const int value);
    ~Currency() { m_value = NULL; }

    const Currency &operator=(const CurrencyData &cd);
    const Currency &operator=(const Currency &rhs);
    const Currency &operator=(const int value);

    const int Value() const;
    const std::string &Name() const;

    inline operator const std::string() const { return Name(); }
    inline operator const int() const { return Value(); }

    // The implicit conversion to int should take care of comparisons
protected:
    const CurrencyData *m_value;

private: 
};

#endif // __AMH__CURRENCY_H__
