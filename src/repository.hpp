#ifndef UDR_REPOSITORY_HPP
#define UDR_REPOSITORY_HPP
#pragma once

#include "package.hpp"

namespace udr
{
    template <typename N, typename V>
    class repository
    {
    public:
        virtual result_type<N,V> query(const N name) const = 0;
        virtual ~repository() {}
    };
}
#endif // UDR_REPOSITORY_HPP
