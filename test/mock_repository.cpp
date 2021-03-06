﻿
#include "mock_repository.hpp"
using namespace udr;

mock_repository::mock_repository(const std::map<std::string,
        std::vector<package<std::string, int>>>& pkgs) : packages(pkgs) {}

result_type<package<std::string,int>> udr::mock_repository::query(const std::string& name) const
{
    _queries.push_back(name);
    auto item_itr = (this->packages).find(name);
    if (item_itr == (this->packages).end())
    {
        return udr::none;
    }
    else
    {
        return item_itr->second;
    }
}


const std::vector<std::string>& mock_repository::queries() const
{
    return _queries;
}
