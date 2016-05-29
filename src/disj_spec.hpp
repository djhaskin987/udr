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
            resolve(std::unique_ptr<const repository<N,V> > r)
        {
            return std::vector<std::string>();
        }
    };
}

#endif // UDR_DISJ_SPEC_HPP
