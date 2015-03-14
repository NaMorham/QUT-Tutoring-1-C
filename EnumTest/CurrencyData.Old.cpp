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

std::map<eCurrency, Currency::CurrencyData*> Currency::CurrencyData::ms_currencyMap;

Currency::CurrencyData::CurrencyData(const eCurrency id, const std::string &name)
	: m_id(id), m_name(name) 
{
	// add to the map so we do not have duplicates
	if (ms_currencyMap.find(id) == ms_currencyMap.end())
	{
		ms_currencyMap.insert(std::pair<eCurrency, CurrencyData*>(id, this));
	}
	else
	{
		ms_currencyMap[id] = this; // bad, but it is not critical
	}
}

Currency::CurrencyData::~CurrencyData()
{
}

const Currency::CurrencyData *Currency::CurrencyData::GetCurrencyData(const eCurrency currency)
{
	// locate in the map
	std::map<eCurrency, CurrencyData*>::const_iterator itr = ms_currencyMap.find(currency);
	return itr == ms_currencyMap.end() ? NULL : itr->second;
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

const Currency::CurrencyData *Currency::GetCurrencyData(const eCurrency currency)
{
	// should not be possible, but just in case
	if ((currency < AUD) || (currency > XEU))
	{
		return NULL;
	}
	return CurrencyData::GetCurrencyData(currency);
}
