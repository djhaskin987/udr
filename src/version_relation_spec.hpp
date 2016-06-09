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
    private:
        class vr_repo : public repository<P>
        {
        private:
            const repository<P>* repo;
            const typename P::version_type& version;
            const R<typename P::version_type>& relation;
        public:
            vr_repo(const repository<P>* repo,
                    const typename P::version_type& version,
                    const R<typename P::version_type>& relation) :
                repo(repo), version(version), relation(relation) {}

            virtual result_type<P> query(
                    const typename P::name_type& name) const
            {
                auto results = repo->query(name);
                if (!results)
                {
                    return results;
                }
                else
                {
                    std::vector<P> filtered;
                    std::copy_if(results->begin(), results->end(),
                            std::back_inserter(filtered),
                            [&](const P& thing) {
                                return relation(version, thing.version);
                            });
                    return filtered;
                }
            }

            virtual ~vr_repo() {}
        };
        name_spec<P> nspec;
        typename P::version_type version;
        R<typename P::version_type> relation;
    public:
        version_relation_spec(const typename P::name_type& name,
                const typename P::version_type& version) :
            nspec(name), version(version), relation() {}

        virtual result_type<P>
            resolve(const repository<P>* r) const
        {
            vr_repo repo(r, version, relation);
            return nspec.resolve(&repo);
        }
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
