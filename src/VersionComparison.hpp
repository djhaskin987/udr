/*
   Copyright 2015 Daniel Jay Haskin

   Licensed under the Apache License, VersionComparison 2.0 (the "License");
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

namespace UDR
{
    enum class ComparisonRelation
    {
        LESS_THAN,
        GREATER_THAN,
        GREATER_EQUAL,
        EQUAL_TO,
        NOT_EQUAL,
        MATCHES
    };

    class VersionComparison;
    using std::unique_ptr<VersionComparison> = VersionComparisonPtr;
    using std::unique_ptr<const VersionComparison> = ConstVersionComparisonPtr;

    class VersionComparison
    {
        public:

            // needed?
            //virtual std::unique_ptr<VersionComparison*> clone() = 0;

            VersionComparison(const VersionComparison&) = delete;
            VersionComparison& operator=(const VersionComparison&) = delete;

            virtual ~VersionComparison() = 0;

            virtual const ConstVersionPtr & version() = 0;
            virtual ComparisonRelation relation() = 0;

            virtual int compare(const unique_ptr<VersionComparison> & other) const = 0;
            virtual bool match(const unique_ptr<VersionComparison> & other) const = 0;
    };
}

#endif // UDR_VERSION_COMPARISON_HPP
