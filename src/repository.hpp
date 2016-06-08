#ifndef UDR_REPOSITORY_HPP
#define UDR_REPOSITORY_HPP
#pragma once

#include <vector>
#include <boost/optional.hpp>

namespace udr
{
    template <typename P>
    using result_type = boost::optional<std::vector<P>>;

    auto const none = boost::none;

    template <typename P>
    class repository
    {
    public:
        virtual result_type<P> query(const typename P::name_type& name) const = 0;
        virtual ~repository() {}
    };
}

#endif // UDR_REPOSITORY_HPP
