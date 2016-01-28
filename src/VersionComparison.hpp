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
#ifndef UDR_VERSION_COMPARISON_HPP
#define UDR_VERSION_COMPARISON_HPP 1
#include <memory>
namespace UDR
{
    class VersionComparison;
    typedef std::unique_ptr<Version> VersionComparisonPtr;
    typedef std::unique_ptr<const Version> ConstVersionComparisonPtr;

    enum class VersionRelation
    {
        LESS_THAN,
        LESS_EQUAL,
        EQUAL_TO,
        MATCHES,
        GREATER_EQUAL,
        GREATER_THAN
    };

    class VersionComparison
    {
        public:

            // needed?
            //virtual std::unique_ptr<Version*> clone() = 0;

            VersionComparison() = default;
            VersionComparison(const VersionComparison&) = delete;
            VersionComparison& operator=(const VersionComparison&) = delete;

            virtual ~VersionComparison()
            { }

            virtual const ConstVersionPtr & version() const = 0;
            virtual VersionRelation relation() const = 0;
            virtual bool satisfiedBy(const ConstVersionPtr & ver) = 0;

            ConstVersionComparisonPtr Create(VersionRelation rel,
                    ConstVersionPtr && ver);
    };
}

#endif
