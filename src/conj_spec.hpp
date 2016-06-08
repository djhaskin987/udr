#ifndef UDR_CONJ_SPEC
#define UDR_CONJ_SPEC
#pragma once

#include "spec.hpp"

namespace udr
{
    template <typename P>
    class conj_spec : public spec<P>
    {
    public:
        virtual const result_type<P>
            resolve(const repository<P>* r) const
        {
            return udr::none;
        }
    };
}

#endif // UDR_CONJ_SPEC
