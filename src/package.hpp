#ifndef UDR_PACKAGE_HPP
#define UDR_PACKAGE_HPP
#pragma once

#include <boost/variant/variant.hpp>
#include <string>
#include <vector>
#include <unordered_map>


namespace udr
{
    
    template <typename N, typename V> class spec;

    template <
        typename N,
        typename V,
        typename L = std::string>
    struct package
    {
        N name;
        V version;
        // Provides can be used by a repo implementation to present the location
        // assigned to this package and present it with differerent name/version
        // pairs, provided in this `provides` map.
        std::unordered_map<N,V> provides;
        std::unique_ptr<spec<N,V>> requirements;
        L location;
    };
    typedef std::vector<std::string> emessages_type;
    template <typename N, typename V, typename L = std::string>
    using result_type = boost::variant<
        emessages_type,
        std::vector<package<N,V,L>>
        >;
}

#endif // UDR_PACKAGE_HPP
