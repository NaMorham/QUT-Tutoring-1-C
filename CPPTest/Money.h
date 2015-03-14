#ifndef __AMH__MONEY_H__
#define __AMH__MONEY_H__

#include <stdint.h>
#include <string>

class Money
{
public:
    // simple constructors
    Money(const int64_t ammount) : m_ammount(ammount) {}
    Money() : Money(0LL) {}

    // construct from partial values (i.e. dollars and cents)
    Money(const long whole, const long part);
    // Assumes a valid string of the format "<whole long>.<2 digits part long>"
    Money(const char *ammount);
    // Copy constructor
    Money(const Money &orig) : m_ammount(orig.GetRawAmmount()) {}

    ~Money() { m_ammount = 0LL; }

    inline const int64_t &GetRawAmmount() const { return m_ammount;  }
    const long GetWholeAmmount() const;
    const long GetPartAmmount() const;
    const std::string ToString() const; // returns a string with "<whole long>.<2 digits part long>"
    const std::string ToStringFull() const; // returns a string with "<whole long>.<part long>"

    // Assumes a valid string of the format "<whole long>.<2 digits part long>"
    void FromString(const char *ammount);
    // Assign from partial values (i.e. dollars and cents)
    void FromPartialValues(const long whole, const long part);
    inline void SetRawAmmount(const int64_t &ammount) { m_ammount = ammount; }

    // precision round value is used to calculate if the final value is
    // rounded up or stays the same when truncated.
    static const long RoundEven(const long amt, const long precisionRound = 500000);

    bool operator<(const Money &rhs) const { return m_ammount < rhs.GetRawAmmount(); }
    bool operator<=(const Money &rhs) const { return m_ammount <= rhs.GetRawAmmount(); }
    bool operator==(const Money &rhs) const { return m_ammount == rhs.GetRawAmmount(); }
    bool operator>(const Money &rhs) const { return !operator<=(rhs); }
    bool operator>=(const Money &rhs) const { return !operator<(rhs); }
    bool operator!=(const Money &rhs) const { return !operator==(rhs); }

private:
    int64_t m_ammount;

    static const int64_t ms_multiplier;
    static const int64_t ms_partsPerWhole;
    static const int64_t ms_wholeMultiplier;
};

#endif // __AMH__MONEY_H__
