#pragma once

// Based on https://accu.org/index.php/journals/2776
// "Profiting from the Folly of Others" by Alastair Harrison

#define HIJACK_FUNC(TAGINT, CLASSNAME, FUNCSIG, RETURNTYPE) \
    template<auto Func> \
    struct HijackFunc##TAGINT { friend RETURNTYPE hijackFunc##TAGINT(CLASSNAME& w) { return (w.*Func)(); } }; \
    template struct HijackFunc##TAGINT<&FUNCSIG>; \
    RETURNTYPE hijackFunc##TAGINT(CLASSNAME& w);

#define HIJACK_VAR(TAGINT, CLASSNAME, VARSIG, RETURNTYPE) \
    template<auto Var> \
    struct HijackVar##TAGINT { friend RETURNTYPE hijackVar##TAGINT(CLASSNAME& w) { return w.*Var; } }; \
    template struct HijackVar##TAGINT<&VARSIG>; \
    RETURNTYPE hijackVar##TAGINT(CLASSNAME& w);
