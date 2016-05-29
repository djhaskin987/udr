#ifndef UDR_CONJ_SPEC
#define UDR_CONJ_SPEC
#pragma once

#include "spec.hpp"

namespace udr
{
    template <typename N, typename V>
    class conj_spec : public spec<N,V>
    {
    public:
        virtual const result_type<N,V>
            resolve(const repository<N, V>* r)
        {
            return std::vector<std::string>();
        }
    };
}

#endif // UDR_CONJ_SPEC
