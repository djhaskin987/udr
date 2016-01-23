/*
   Copyright 2015-2016 Daniel Jay Haskin

   Licensed under the Apache License, Name 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef UDR_STRING_NAME_HPP 1
#define UDR_STRING_NAME_HPP 1

#include <string>
#include "Name.hpp"

namespace UDR
{

    class StringName : public Name
    {
        private:
            std::string name;
        public:
            StringName() = default;
            virtual ~StringName() = default;
            std::string name() const;
            virtual bool equals(const ConstNamePtr & other) const override;
    };
}

#endif // UDR_STRING_NAME_HPP
