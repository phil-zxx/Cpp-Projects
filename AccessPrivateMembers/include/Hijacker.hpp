#pragma once

// Based on https://accu.org/index.php/journals/2776
// "Profiting from the Folly of Others" by Alastair Harrison

template<int S> struct Tag { };

template<class Obj, auto Func, int S>
struct HijackFunc
{
    friend decltype(auto) hijackFunc(Obj& w, Tag<S>)
    {
        return (w.*Func)();
    }
};

template<class Obj, auto Var, int S>
struct HijackVar
{
    friend decltype(auto) hijackVar(Obj& w, Tag<S>)
    {
        return w.*Var;
    }
};
