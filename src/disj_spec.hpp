#ifndef UDR_DISJ_SPEC_HPP
#define UDR_DISJ_SPEC_HPP
#pragma once

namespace udr
{
    template <typename N, typename V>
    class disj_spec : public spec<N,V>
    {
    public:
        virtual const result_type<N,V>
            resolve(const repository* r) const
        {
            return udr::none;
        }
    };
}

#endif // UDR_DISJ_SPEC_HPP
