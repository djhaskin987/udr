#ifndef UDR_SPEC_HPP
#define UDR_SPEC_HPP
#pragma once
#include "package.hpp"
#include "repository.hpp"

#include <memory>

namespace udr
{
    template <typename N, typename V>
    class spec
    {
        public:
            virtual result_type<N, V>
                resolve(const repository<N, V>* r) const = 0;
    };
}

#endif // UDR_SPEC_HPP
