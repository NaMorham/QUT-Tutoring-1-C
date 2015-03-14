#include "Money.h"
#include <sstream>
#include <iomanip>

// ---------------------------------------------------------------------------
// local constants
static const size_t BUF_SIZE = 256;


// ---------------------------------------------------------------------------
// Utility functions
template<class T>
const T &GetMin(const T &val, const T &min) { return val < min ? val : min; }

template<class T>
const T &GetMax(const T &val, const T &max) { return val > max ? val : max; }

template<class T>
const T &LimitVal(const T &val, const T &min, const T &max) { return GetMin(GetMax(val, min), max); }

long GetMillionthVal(const char *str)
{
    if (str && *str) // safety check, we must have a string
    {
        char buf[BUF_SIZE];
        memset(buf, 0, sizeof(char) * BUF_SIZE); // init buffer to null

        if (sscanf(str, ".%s", buf) == 1)   // must be a numerical value preceeded by a decimal
        {
            static const char *nums = "123456789";  // only 1-9 are valid as a last digit

            std::string tmp(buf);                   // lazy use of the stl string class find last
            size_t pos = tmp.find_last_of(nums);

            int cutoff = (pos < 8 ? pos + 1 : 8);   // calculate the cutoff, because we assume millionths it is 6 digits
            buf[cutoff] = 0;                        // get rid of the excess precision

            long sval = 0;          // scan what is left to get
            if (sscanf(buf, "%d", &sval) == 1)
            {
                long exponent = LimitVal(7 - (int)pos, 0, 8);   // how much do we need to multiply 10 by to calculate how many millionths

                long val = sval * long(pow(10, exponent));
                return val;
            }
        }
    }

    return 0L;
}


// ---------------------------------------------------------------------------
const int64_t Money::ms_multiplier = 1000000;  // multiplier to make 1 "part"
const int64_t Money::ms_partsPerWhole = 100;   // multiplier to make 1 whole from a part
const int64_t Money::ms_wholeMultiplier = ms_partsPerWhole * ms_multiplier;

// Visual studio does not support this
#ifndef snprintf
#define snprintf _snprintf
#endif

Money::Money(const long whole, const long part)
{
    FromPartialValues(whole, part);
}

// Assumes a valid string of the format "<whole long>.<part long>"
Money::Money(const char *ammount)
{
    FromString(ammount);
}

const long Money::GetWholeAmmount() const
{
    return long(m_ammount / ms_wholeMultiplier);
}

const long Money::GetPartAmmount() const
{
    return long(m_ammount - (GetWholeAmmount() * ms_wholeMultiplier));
}

// returns a string with "<whole long>.<2 digits part long>"
const std::string Money::ToString() const
{
    std::stringstream ss, ssPart;
    ss << GetWholeAmmount() << ".";
    ssPart << RoundEven(GetPartAmmount());
    ss << std::setw(2) << std::setfill('0') << ssPart.str().substr(0, 2);
    return ss.str();
}

// returns a string with "<whole long>.<part long>"
const std::string Money::ToStringFull() const
{
    std::stringstream ss;
    ss << GetWholeAmmount() << ".";
    ss << std::setfill('0') << std::setw(8) << GetPartAmmount();
    return ss.str();
}

// Assumes a valid string of the format "<whole long>.<part long>"
void Money::FromString(const char *ammount)
{
    if (ammount && *ammount)
    {
        char buf[BUF_SIZE];
        memset(buf, 0, BUF_SIZE*sizeof(char));

        long whole(0), part(0);
        if (std::sscanf(ammount, "%d.%s", &whole, &buf) == 2)
        {
            if (std::sscanf(buf, "%d", &part) == 1)
            {
                // make sure we have the '.'
                std::string tmp(".");
                tmp += buf;
                part = int64_t(GetMillionthVal(tmp.c_str()));
                m_ammount = (int64_t)whole * ms_wholeMultiplier;
                m_ammount += (int64_t)part;
                return; // done
            }
        }
        else if (std::sscanf(ammount, ".%s", &buf) == 1)
        {
            // special case
            m_ammount = int64_t(GetMillionthVal(ammount));
            return; // done
        }
        else if (std::sscanf(ammount, "%d", &whole) == 1)
        {
            FromPartialValues(whole, 0);
            return; // done
        }
        // if we could not read both values for some reson then drop through and set empty
    }

    m_ammount = 0LL;
}

// Assign from partial values (i.e. dollars and cents)
void Money::FromPartialValues(const long whole, const long part)
{
    int64_t pt = (int64_t)part * ms_multiplier;
    int64_t wl = (int64_t)whole * ms_partsPerWhole * ms_multiplier;
    m_ammount = pt + wl;
}

const long Money::RoundEven(const long amt, const long precisionRound /*= 500000*/)
{
    // add the precisions rounding ammount
    long result = amt + precisionRound; 
    // truncate - abusing the integer division truncation
    result /= ms_multiplier;
    result *= ms_multiplier;

    return result;
}
