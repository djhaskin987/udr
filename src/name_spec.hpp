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
        name_spec(const N& name) : name(name) {}
        virtual result_type<N,V>
            resolve(const repository<N, V>* r) const
        {
            auto results = r->query(name);
            if (std::vector<package<N,V> >* packages =
                    boost::get<std::vector<package<N,V>>>(&results))
            {
                if (packages->size() == 0)
                {
                    return emessages_type {
                        std::string() +
                            "While resolving a package name, matching packages were returned when " +
                            "query `" + name + "` was used."
                    };
                }
                else
                {
                    return std::vector<package<N,V>> {
                        *(packages->begin())
                    };
                }
            }
            else
            {
                emessages_type& messages = boost::get<emessages_type>(results);
                messages.push_back(
                        std::string("While resolving a package name, the ") +
                        "repository reported an error.");
                return messages;
            }
        }
    private:
        N name;
    };
    template <typename N, typename V>
    std::unique_ptr<spec<N,V>> make_name_spec(const N& name)
    {
        return std::unique_ptr<spec<N,V>>{ new name_spec<N,V>(name) };
    }

}

#endif // UDR_NAME_SPEC
