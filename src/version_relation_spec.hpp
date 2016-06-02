#ifndef UDR_VERSION_RELATION_SPEC
#define UDR_VERSION_RELATION_SPEC
#pragma once

#include <functional>
#include <memory>
#include "spec.hpp"
#include "name_spec.hpp"

namespace udr
{

    template <typename N, typename V,
             template <typename T> typename R = std::greater_equal>
    class version_relation_spec : public spec<N,V>
    {
    public:
        version_relation_spec(const N& name, const V& version) :
            nspec(name), version(version), relation() {}

        virtual result_type<N,V>
            resolve(const repository<N, V>* r) const
        {

            return emessages_type();
        }
    private:
        name_spec<N,V> nspec;
        V version;
        R<V> relation;
    };

    template <typename N, typename V,
             template <typename T> typename R = std::greater_equal>
    std::unique_ptr<spec<N,V>>
    make_vr_spec(const N& name, const V& version)
    {
        return std::unique_ptr<spec<N,V>>{
            new version_relation_spec<N,V,R>(name, version)
        };
    }
}

#endif // UDR_VERSION_RELATION_SPEC
