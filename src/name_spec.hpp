#ifndef UDR_NAME_SPEC
#define UDR_NAME_SPEC
#pragma once

#include "spec.hpp"
#include <memory>
namespace udr
{
    template <typename N, typename V>
    class name_spec : public spec<N,V>
    {
    public:
        virtual result_type<N,V>
            resolve(const repository<N, V>* r) const
        {
            return std::vector<std::string>{};
        }
    };
    template <typename N, typename V>
    std::unique_ptr<spec<N,V>> make_name_spec(const N& name)
    {
        return std::unique_ptr<spec<N,V>>{ new name_spec<N,V>{} };
    }

}

#endif // UDR_NAME_SPEC
