#ifndef UDR_MOCK_REPOSITORY_HPP
#define UDR_MOCK_REPOSITORY_HPP
#pragma once

#include <vector>
#include <map>
#include <string>
#include "package.hpp"
#include "repository.hpp"

namespace udr
{
    class mock_repository : public repository<udr::package<std::string, int>>
    {
    public:
        mock_repository(const std::map<std::string,
                std::vector<udr::package<std::string, int>>>& pkgs);
        virtual ~mock_repository() {}

        virtual result_type<udr::package<std::string, int>>
            query(const std::string& name) const;
        const std::vector<std::string>& queries() const;

    private:
        std::map<std::string, std::vector<package<std::string, int> > >
            packages = {};
        mutable std::vector<std::string> _queries = {};
    };
}

#endif
