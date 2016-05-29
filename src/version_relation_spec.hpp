#ifndef UDR_VERSION_RELATION_SPEC
#define UDR_VERSION_RELATION_SPEC
#pragma once

#include <functional>
#include "spec.hpp"

namespace udr
{

    template <typename N, typename V,
             template <typename T> typename R = std::equal_to>
    class version_relation_spec : public spec<N,V>
    {
    public:
        virtual const result_type<N,V>
            resolve(const repository<N, V>* r) const
        {
            return std::vector<std::string>();
        }
    private:
        R<V> relation;
    };
}

#endif // UDR_VERSION_RELATION_SPEC
