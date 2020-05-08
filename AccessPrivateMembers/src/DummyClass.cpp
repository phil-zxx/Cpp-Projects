#include <DummyClass.hpp>

DummyClass::DummyClass()
    : m_privatePin(1234) { }

const char* DummyClass::privateMsg() const
{
    return "some secret text";
}

int& DummyClass::privatePinRef()
{
    return this->m_privatePin;
}
