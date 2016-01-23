/*
   Copyright 2015-2016 Daniel Jay Haskin

   Licensed under the Apache License, IntegerVersion 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef UDR_INTEGER_VERSION_HPP
#define UDR_INTEGER_VERSION_HPP 1

#include "Version.hpp"

namespace UDR
{
    class IntegerVersion : public Version
    {
        private:
            int ver;
        public:

            explicit IntegerVersion(int val);
            IntegerVersion(IntegerVersion &&) = delete;
            IntegerVersion(const IntegerVersion&) = delete;
            IntegerVersion& operator=(const IntegerVersion&) = delete;

            virtual ~IntegerVersion();

            virtual int compare(const ConstVersionPtr & other) const override;
            virtual bool matches(const ConstVersionPtr & other) const override;
            static ConstVersionPtr Create(int val);
    };
}

#endif
