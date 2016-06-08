#ifndef UDR_NAME_SPEC
#define UDR_NAME_SPEC
#pragma once

#include "spec.hpp"
#include <memory>
namespace udr
{

    template <typename P>
    class name_spec : public spec<P>
    {
    public:
        name_spec(const typename P::name_type& name) : name(name) {}
        virtual result_type<P>
            resolve(const repository<P>* r) const
        {
            auto results = r->query(name);
            if (results)
            {
                if (results->size() == 0)
                {
                    return udr::none;
                }
                else
                {
                    return std::vector<P> {
                        *(results->begin())
                    };
                }
            }
            else
            {
                return udr::none;
            }
        }
    private:
        typename P::name_type name;
    };

    template <typename P>
    std::unique_ptr<spec<P>> make_name_spec(const typename P::name_type& name)
    {
        return std::unique_ptr<spec<P>>{ new name_spec<P>(name) };
    }
}

#endif // UDR_NAME_SPEC
