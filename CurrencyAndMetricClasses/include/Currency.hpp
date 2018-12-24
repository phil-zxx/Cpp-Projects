#pragma once


class CurrencyChar
{
public:
    CurrencyChar(const char ccyCode[4]);

private:
    char m_ccyCode[4];
};

class CurrencyInt
{
public:
    CurrencyInt(const int& ccyHash);

private:
    int m_ccyHash;
};