#ifndef __AMH__CURRENCY_DATA_H__
#define __AMH__CURRENCY_DATA_H__

#include <string>
#include <map>

/**
AUD("Australian Dollar"),
CAD("Canadian Dollar"),
GBP("Great British Pound"),
JPY("Japanese Yen"),
USD("United States Dollar"),
XEU("European Euro");
 */
enum eCurrency { AUD, CAD, GBP, JPY, USD, XEU };

class Currency
{
public:
    class CurrencyData
    {
    public:
        CurrencyData(const eCurrency id, const std::string &name);
        ~CurrencyData();

        operator const eCurrency() const { return m_id; }
        operator const std::string &() const { return m_name; }

        const std::string &Name() const { return m_name; }
        const eCurrency ID() const { return m_id;  }

        const bool operator<(const eCurrency rhs) const;
        const bool operator<(const CurrencyData &rhs) const;
        const bool operator<=(const eCurrency rhs) const;
        const bool operator<=(const CurrencyData &rhs) const;
        const bool operator==(const eCurrency rhs) const;
        const bool operator==(const CurrencyData &rhs) const;
        const bool operator>(const eCurrency rhs) const;
        const bool operator>(const CurrencyData &rhs) const;
        const bool operator>=(const eCurrency rhs) const;
        const bool operator>=(const CurrencyData &rhs) const;
        const bool operator!=(const eCurrency rhs) const;
        const bool operator!=(const CurrencyData &rhs) const;

    private:
        eCurrency m_id;
        std::string m_name;
        //std::string m_abrev;    // not required by spec but should be used

    public:
    };

    static const CurrencyData AUD;
    static const CurrencyData CAD;
    static const CurrencyData GBP;
    static const CurrencyData JPY;
    static const CurrencyData USD;
    static const CurrencyData XEU;

private:
    // no creating or destroying currencies
    Currency() {}
    ~Currency() {}
}; // namespace currency

#endif // __AMH__CURRENCY_DATA_H__
