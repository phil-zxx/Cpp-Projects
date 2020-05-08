#include <Hijacker.hpp>
#include <DummyClass.hpp>

template struct HijackFunc<DummyClass, &DummyClass::privateMsg,    0>;
template struct HijackFunc<DummyClass, &DummyClass::privatePinRef, 1>;
template struct HijackVar <DummyClass, &DummyClass::m_privatePin,  0>;

int main()
{
    DummyClass obj;

    // auto privateMsg  = obj.privateMsg();     <-- Does not compile, because function DummyClass::privateMsg    and
    // auto privatePin1 = obj.privatePinRef();                                function DummyClass::privatePinRef and
    // auto privatePin2 = obj.m_privatePin;                                   member   DummyClass::m_privatePin  are inaccessible
    
    auto getMsg  = [&]() { return hijackFunc(obj, Tag<0>{}); };
    auto getPin1 = [&]() { return hijackFunc(obj, Tag<1>{}); };
    auto getPin2 = [&]() { return hijackVar (obj, Tag<0>{}); };
    auto privateMsg  = getMsg();   // Call private function DummyClass::privateMsg
    auto privatePin1 = getPin1();  // Call private function DummyClass::privatePinRef
    auto privatePin2 = getPin2();  // Obtain private member DummyClass::m_privatePin

    auto setPin1 = [&](int newPin) { hijackFunc(obj, Tag<1>{}) = newPin; };
    auto setPin2 = [&](int newPin) { hijackVar (obj, Tag<0>{}) = newPin; };
    setPin1(8888);  // Obtain reference to private member DummyClass::m_privatePin (via DummyClass::privatePinRef) and set it to 8888
    setPin2(9999);  // Obtain reference to private member DummyClass::m_privatePin directly and set it to 9999

    return 0;
}
