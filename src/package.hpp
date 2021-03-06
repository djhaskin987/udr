#ifndef UDR_PACKAGE_HPP
#define UDR_PACKAGE_HPP
#pragma once

#include <string>
#include <map>
#include <memory>

namespace udr
{
    template <typename P> class spec;

    /* Reference implementation for the `package` concept. */
    template <typename N, typename V, typename L = std::string>
    struct package
    {
        typedef N name_type;
        typedef V version_type;
        N name;
        V version;
        L location;

        // Provides functionality can be done completely on the repo side, why
        // do it here?
        // Requirements and conflicts, though, are on point.
        std::shared_ptr<const spec<package<N,V,L>>> requirements;
        std::map<N,std::vector<std::function<bool(const package<N,V,L>&)>>>
            conflicts;
    };
}

#endif // UDR_PACKAGE_HPP
