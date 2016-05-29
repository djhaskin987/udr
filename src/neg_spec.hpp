#ifndef UDR_NEG_SPEC
#define UDR_NEG_SPEC
#pragma once

#include "spec.hpp"

namespace udr
{
    template <typename N, typename V>
    class neg_spec : public spec<N,V>
    {
    public:
        virtual const result_type<N,V>
            resolve(const repository* r)
        {
            return std::vector<std::string>();
        }
    };
}

#endif // UDR_NEG_SPEC
