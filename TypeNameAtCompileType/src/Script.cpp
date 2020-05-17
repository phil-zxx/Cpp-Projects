#include <TypeInfo.hpp>
#include <iostream>

namespace MyOwn
{
    class TestClass { };
}

template<class T>
struct DerivedClass { };

int main()
{
    std::cout << "TypeInfo::getTypeName<int>()               = '" << TypeInfo::getTypeName<int>()               << "'\n"
              << "TypeInfo::getTypeName<double>()            = '" << TypeInfo::getTypeName<double>()            << "'\n"
              << "TypeInfo::getTypeName<MyOwn::TestClass>()  = '" << TypeInfo::getTypeName<MyOwn::TestClass>()  << "'\n"
              << "TypeInfo::getTypeName<DerivedClass<int>>() = '" << TypeInfo::getTypeName<DerivedClass<int>>() << "'\n";

    return 0;
}
