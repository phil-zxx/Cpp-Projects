#include <Hijacker.hpp>
#include <DummyClass.hpp>

template struct HijackFunc<DummyClass, &DummyClass::privateFunc1,   1>;
template struct HijackFunc<DummyClass, &DummyClass::privateFunc2,   2>;
template struct HijackVar<DummyClass,  &DummyClass::secretVariable, 1>;

int main()
{
    DummyClass obj;

    // auto secretText1 = obj.privateFunc1();  <-- Does not compile, because function DummyClass::privateFunc1 and
    // auto secretText2 = obj.privateFunc2();                                function DummyClass::privateFunc2 and
    // auto secretValue = obj.secretVariable;                                member   DummyClass::secretVariable are inaccessible

    auto secretText1 = hijackFunc(obj, Tag<1>{});
    auto secretText2 = hijackFunc(obj, Tag<2>{});
    auto secretValue = hijackVar (obj, Tag<1>{});

    return 0;
}
