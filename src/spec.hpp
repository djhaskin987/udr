#ifndef UDR_SPEC_HPP
#define UDR_SPEC_HPP
#pragma once
#include "package.hpp"
#include "repository.hpp"

#include <memory>

namespace udr
{
    template <typename P>
    class spec
    {
        public:
            virtual result_type<P>
                resolve(const repository<P>* r) const = 0;
    };
}

#endif // UDR_SPEC_HPP
