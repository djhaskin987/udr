/*
   Copyright 2016 Daniel Jay Haskin

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef UDR_RESOLVER_HPP
#define UDR_RESOLVER_HPP 1
#include <boost/variant.hpp>
#include <algorithm>

namespace UDR {
    template <typename PackageType, typename QueryType>
        class Resolver
        {
            private:
                std::map<typename PackageType::NameType,
                      typename PackageType::VersionType> alreadyInstalled;
                QueryType query;

                boost::variant<std::vector<PackageType>,
                    std::vector<typename PackageType::NameType> >
                        resolve(const std::vector<PackageSpec<PackageType> >& requirements)
                        {
                            std::vector<PackageType> result;

                            for (auto requirement = requirements.cbegin();
                                    requirement != requirements.cend(); requirement++) {
                                auto answer = query(requirement->name);
                                if (!answer) {
                                    return std::vector<typename PackageType::NameType>{ requirement->name };
                                }
                                else {
                                    result.push_back(*(answer->begin()));
                                }
                            }
                            return result;
                        }
            public:
                typedef typename PackageType::NameType NameType;
                typedef typename PackageType::VersionType VersionType;

                Resolver() = default;
                Resolver(const Resolver& other) = default;
                Resolver(Resolver&& other) = default;
                ~Resolver() = default;
                Resolver& operator= (const Resolver& other) {
                    return (*this = std::move(Resolver(other)));
                }
                Resolver& operator= (Resolver&& other) {
                    this->alreadyInstalled = std::move(other.alreadyInstalled);
                    this->query = std::move(other.query);
                    return *this;
                }

                Resolver(const QueryType& q)
                    : query(q)
                    , alreadyInstalled()
                {}

                Resolver(QueryType&& q)
                    : query(std::move(q))
                    , alreadyInstalled()
                {}

                bool operator== (const Resolver<PackageType, QueryType>& other) {
                    return this->alreadyInstalled == other.alreadyInstalled;
                }

                Resolver<PackageType, QueryType>&
                    setAlreadyInstalled(const std::map<typename PackageType::NameType,
                            typename PackageType::VersionType>& installed) {
                        this->alreadyInstalled = installed;
                        return *this;
                    }

                Resolver<PackageType, QueryType>&
                    setAlreadyInstalled(std::map<typename PackageType::NameType,
                            typename PackageType::VersionType>&& installed) {
                        this->alreadyInstalled = std::move(installed);
                        return *this;
                    }

                boost::variant<std::vector<PackageType>,
                    std::vector<typename PackageType::NameType> >
                        operator ()(const std::vector<PackageSpec<PackageType> >& requirements)
                        {
                            this->resolve(requirements);
                        }
        };
}

#endif // UDR_RESOLVER_HPP
