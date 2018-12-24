#include <Currency.hpp>


CurrencyChar::CurrencyChar(const char ccyCode[4])
{
    m_ccyCode[0] = m_ccyCode[0];
    m_ccyCode[1] = m_ccyCode[1];
    m_ccyCode[2] = m_ccyCode[2];
    m_ccyCode[3] = m_ccyCode[3];
}

CurrencyInt::CurrencyInt(const int& ccyHash)
    : m_ccyHash(ccyHash) { }
