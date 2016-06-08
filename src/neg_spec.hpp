#ifndef UDR_NEG_SPEC
#define UDR_NEG_SPEC
#pragma once

#include "spec.hpp"

namespace udr
{
    /* Meant to embody a conflict. */
    template <typename P>
    class neg_spec : public spec<P>
    {
    public:
        virtual const result_type<P>
            resolve(const repository<P>* r) const
        {
            return udr::none;
        }
    };
}

#endif // UDR_NEG_SPEC
