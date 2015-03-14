#include "Currency.h"
#include <exception>
#include <stdexcept>

// ---------------------------------------------------------------------------
// Currency Data class
int CurrencyData::ms_val = 0;
std::vector<CurrencyData *> CurrencyData::ms_data;

CurrencyData::CurrencyData(const std::string &name)
    : m_name(name)
{
    m_value = ms_val++;
    ms_data.push_back(this); // the index in the vector must match the value of the item
}

CurrencyData::~CurrencyData()
{
    // make sure we remove the pointer to the data
    if ((int)ms_data.size() > m_value)
    {
        ms_data[m_value] = NULL;
    }
    // invalidate
    m_name = "";
    m_value = -1;
}

const bool CurrencyData::operator<(const int rhs) const
{
    return m_value < rhs;
}
const bool CurrencyData::operator<(const CurrencyData &rhs) const
{
    return m_value < rhs.Value();
}

const bool CurrencyData::operator<=(const int rhs) const
{
    return m_value <= rhs;
}
const bool CurrencyData::operator<=(const CurrencyData &rhs) const
{
    return m_value <= rhs.Value();
}

const bool CurrencyData::operator==(const int rhs) const
{
    return m_value == rhs;
}
const bool CurrencyData::operator==(const CurrencyData &rhs) const
{
    return m_value == rhs.Value();
}

const bool CurrencyData::operator>(const int rhs) const
{
    return m_value > rhs;
}
const bool CurrencyData::operator>(const CurrencyData &rhs) const
{
    return m_value > rhs.Value();
}

const bool CurrencyData::operator>=(const int rhs) const
{
    return m_value >= rhs;
}
const bool CurrencyData::operator>=(const CurrencyData &rhs) const
{
    return m_value > rhs.Value();
}

const bool CurrencyData::operator!=(const int rhs) const
{
    return m_value != rhs;
}
const bool CurrencyData::operator!=(const CurrencyData &rhs) const
{
    return m_value != rhs.Value();
}

const CurrencyData *CurrencyData::Find(const int value)
{
    // for now we assume that value is the same as index
    // in future this hsould allow for strange enum ranges (to match the base language)
    if ((value < 0) || (value >= (int)ms_data.size()))
    {
        throw std::out_of_range("Invalid enum value");
        return NULL; // BAD PROGRAMMER
    }
    else
    {
        return ms_data[value];
    }
}

const CurrencyData Currency::AUD("Australian Dollar");
const CurrencyData Currency::CAD("Canadian Dollar");
const CurrencyData Currency::GBP("Great British Pound");
const CurrencyData Currency::JPY("Japanese Yen");
const CurrencyData Currency::USD("United States Dollar");
const CurrencyData Currency::XEU("European Euro");


// Currency interface
Currency::Currency()
{
    m_value = CurrencyData::Find(0); // it should be safe to just use the cd passed in, but play it safe
}

Currency::Currency(const CurrencyData &cd)
{
    m_value = CurrencyData::Find(cd.Value()); // it should be safe to just use the cd passed in, but play it safe
}

Currency::Currency(const Currency &orig)
{
    m_value = CurrencyData::Find(orig.Value()); // it should be safe to just use the cd passed in, but play it safe
}

Currency::Currency(const int value)
{
    m_value = CurrencyData::Find(value);
}

const Currency &Currency::operator = (const CurrencyData &cd)
{
    m_value = CurrencyData::Find(cd.Value());
    return *this;
}

const Currency &Currency::operator = (const Currency &rhs)
{
    m_value = CurrencyData::Find(rhs.Value());
    return *this;
}

const Currency &Currency::operator = (const int value)
{
    m_value = CurrencyData::Find(value);
    return *this;
}

const int Currency::Value() const
{
    // assume m_value is a sane index
    assert(m_value != NULL);
    return m_value->Value();
}

const std::string &Currency::Name() const
{
    assert(m_value != NULL);
    return m_value->Name();
}
