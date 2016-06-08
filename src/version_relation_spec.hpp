#ifndef UDR_VERSION_RELATION_SPEC
#define UDR_VERSION_RELATION_SPEC
#pragma once

#include <functional>
#include <memory>
#include "spec.hpp"
#include "name_spec.hpp"

namespace udr
{

    template <typename P,
             template <typename T> typename R = std::greater_equal>
    class version_relation_spec : public spec<P>
    {
    public:
        version_relation_spec(const typename P::name_type& name,
                const typename P::version_type& version) :
            nspec(name), version(version), relation() {}

        virtual result_type<P>
            resolve(const repository<P>* r) const
        {
            return udr::none;
        }
    private:
        name_spec<P> nspec;
        typename P::version_type version;
        R<typename P::version_type> relation;
    };

    template <typename P,
             template <typename T> typename R = std::greater_equal>
    std::unique_ptr<spec<P>>
    make_vr_spec(const typename P::name_type& name,
            const typename P::version_type& version)
    {
        return std::unique_ptr<spec<P>>{
            new version_relation_spec<P,R>(name, version)
        };
    }
}

#endif // UDR_VERSION_RELATION_SPEC
