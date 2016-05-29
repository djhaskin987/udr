#ifndef UDR_NAME_SPEC
#define UDR_NAME_SPEC
#pragma once

#include "spec.hpp"

namespace udr
{
    template <typename N, typename V>
    class name_spec : public spec<N,V>
    {
    public:
        virtual const result_type<N,V>
            resolve(const repository<N, V>* r) const
        {
            return std::vector<std::string>();
        }
    };
}

#endif // UDR_NAME_SPEC
