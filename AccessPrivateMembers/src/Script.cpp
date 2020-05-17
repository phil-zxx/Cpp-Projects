#include <Hijacker.hpp>
#include <DummyClass.hpp>
#include <type_traits>

HIJACK_FUNC(0, DummyClass, DummyClass::privateMsg,    const char*)
HIJACK_FUNC(1, DummyClass, DummyClass::privatePinRef, int&)
HIJACK_VAR (0, DummyClass, DummyClass::m_privatePin,  int&)

int main()
{
    DummyClass obj;

    // auto privateMsg  = obj.privateMsg();     <-- Does not compile, because function DummyClass::privateMsg    and
    // auto privatePin1 = obj.privatePinRef();                                function DummyClass::privatePinRef and
    // auto privatePin2 = obj.m_privatePin;                                   member   DummyClass::m_privatePin  are inaccessible
    
    const auto getMsg  = [&]() { return hijackFunc0(obj); };
    const auto getPin1 = [&]() { return hijackFunc1(obj); };
    const auto getPin2 = [&]() { return hijackVar0 (obj); };
    const auto privateMsg  = getMsg();   // Call private function DummyClass::privateMsg
    const auto privatePin1 = getPin1();  // Call private function DummyClass::privatePinRef
    const auto privatePin2 = getPin2();  // Obtain private member DummyClass::m_privatePin

    const auto setPin1 = [&](int newPin) { hijackFunc1(obj) = newPin; };
    const auto setPin2 = [&](int newPin) { hijackVar0 (obj) = newPin; };
    setPin1(8888);  // Obtain reference to private member DummyClass::m_privatePin (via DummyClass::privatePinRef) and set it to 8888
    setPin2(9999);  // Obtain reference to private member DummyClass::m_privatePin directly and set it to 9999

    return 0;
}
