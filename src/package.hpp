#ifndef UDR_PACKAGE_HPP
#define UDR_PACKAGE_HPP
#pragma once

#include <boost/variant.hpp>
#include <string>
#include <vector>

namespace udr
{
    template <typename N, typename V>
    class package
    {
        public:
            N name;
            V version;
            std::string location;
    };
    template <typename N, typename V>
    using result_type = boost::variant<
        std::vector<std::string>,
        std::vector<package<N, V> > >;
}

#endif // UDR_PACKAGE_HPP
