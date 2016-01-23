/*
   Copyright 2015 Daniel Jay Haskin

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
#ifndef UDR_NAME_HPP 1
#define UDR_NAME_HPP 1

#include <exception>
#include <memory>

namespace UDR
{
    class Name;
    using std::unique_ptr<Name> = NamePtr;
    using std::unique_ptr<const Name> = const ConstNamePtr;

    class NameMismatchException : public std::exception
    {
        public:
            virtual const char * what() const noexcept
            {
                return "Incompatible name types";
            }
    };

    class Name
    {
        public:

            // needed?
            //virtual std::unique_ptr<Name*> clone() = 0;
            Name() = default;
            Name(const Name&) = delete;
            Name& operator=(const Name&) = delete;

            virtual ~Name()
            { }

            virtual bool equals(const ConstNamePtr & other) const = 0;
    };
}

#endif // UDR_NAME_HPP
