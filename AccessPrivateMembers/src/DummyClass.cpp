#include <DummyClass.hpp>

DummyClass::DummyClass()
    : secretVariable(1234) { }

const char* DummyClass::privateFunc1()
{
    return "secret Gadget text";
}

const char* DummyClass::privateFunc2()
{
    return "more secret Gadget text";
}
