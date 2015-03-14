#include "CurrencyData.h"

/**
  Define these explicity at the top so it is easier to add new ones
 */
const Currency::CurrencyData Currency::AUD(::AUD, "Australian Dollar");
const Currency::CurrencyData Currency::CAD(::CAD, "Canadian Dollar");
const Currency::CurrencyData Currency::GBP(::GBP, "Great British Pound");
const Currency::CurrencyData Currency::JPY(::JPY, "Japanese Yen");
const Currency::CurrencyData Currency::USD(::USD, "United States Dollar");
const Currency::CurrencyData Currency::XEU(::XEU, "European Euro");

Currency::CurrencyData::CurrencyData(const eCurrency id, const std::string &name)
    : m_id(id), m_name(name) 
{
}

Currency::CurrencyData::~CurrencyData()
{
}

const bool Currency::CurrencyData::operator<(const eCurrency rhs) const
{
    return m_id < rhs;
}
const bool Currency::CurrencyData::operator<(const CurrencyData &rhs) const
{
    return m_id < rhs.ID();
}

const bool Currency::CurrencyData::operator<=(const eCurrency rhs) const
{
    return m_id <= rhs;
}
const bool Currency::CurrencyData::operator<=(const CurrencyData &rhs) const
{
    return m_id <= rhs.ID();
}

const bool Currency::CurrencyData::operator==(const eCurrency rhs) const
{
    return m_id == rhs;
}
const bool Currency::CurrencyData::operator==(const CurrencyData &rhs) const
{
    return m_id == rhs.ID();
}

const bool Currency::CurrencyData::operator>(const eCurrency rhs) const
{
    return m_id > rhs;
}
const bool Currency::CurrencyData::operator>(const CurrencyData &rhs) const
{
    return m_id > rhs.ID();
}

const bool Currency::CurrencyData::operator>=(const eCurrency rhs) const
{
    return m_id >= rhs;
}
const bool Currency::CurrencyData::operator>=(const CurrencyData &rhs) const
{
    return m_id > rhs.ID();
}

const bool Currency::CurrencyData::operator!=(const eCurrency rhs) const
{
    return m_id != rhs;
}
const bool Currency::CurrencyData::operator!=(const CurrencyData &rhs) const
{
    return m_id != rhs.ID();
}
