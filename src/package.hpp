#ifndef UDR_PACKAGE_HPP
#define UDR_PACKAGE_HPP
#pragma once

#include <boost/variant/variant.hpp>
#include <string>
#include <vector>

namespace udr
{
    template <typename N, typename V>
    struct package
    {
        N name;
        V version;
        std::string location;
    };
    typedef std::vector<std::string> emessages_type;
    template <typename N, typename V>
    using result_type = boost::variant<
        emessages_type,
        std::vector<package<N, V> > >;
}

#endif // UDR_PACKAGE_HPP
