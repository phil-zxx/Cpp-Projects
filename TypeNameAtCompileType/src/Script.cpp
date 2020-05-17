#include <TypeInfo.hpp>

namespace MyOwn
{
    class TestClass { };
}

template<class T, class U>
struct DerivedClass { };

int main()
{
    static_assert(TypeInfo::getTypeName<int>()    == "int");
    static_assert(TypeInfo::getTypeName<float>()  == "float");
    static_assert(TypeInfo::getTypeName<double>() == "double");

    #if defined(__clang__) || defined(__GNUC__)
        static_assert(TypeInfo::getTypeName<MyOwn::TestClass>()          == "MyOwn::TestClass");
        static_assert(TypeInfo::getTypeName<DerivedClass<int, double>>() == "DerivedClass<int, double>");
    #else
        static_assert(TypeInfo::getTypeName<MyOwn::TestClass>()          == "class MyOwn::TestClass");
        static_assert(TypeInfo::getTypeName<DerivedClass<int, double>>() == "struct DerivedClass<int,double>");
    #endif

    return 0;
}
