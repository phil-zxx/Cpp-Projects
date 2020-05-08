#pragma once

class DummyClass
{
public:
    DummyClass();

private:
    const char* privateMsg() const;
    int& privatePinRef();

    int m_privatePin;
};
