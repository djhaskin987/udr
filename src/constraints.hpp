/*
   Copyright 2015 Daniel Jay Haskin

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
#ifndef UDR_CONSTRAINTS_HPP
#define UDR_CONSTRAINTS_HPP 1
namespace udr {

    template <typename version_type>
    class version_constraint
    {
    public:
        virtual bool operator ()(const version_type & a, const version_type & b) = 0;
        virtual std::string name() = 0;
    };

    template <typename version_type>
    class less : public version_constraint<version_type>
    {
    public:
        template <typename version_type>
        virtual bool operator ()(const version_type & a,
                                 const version_type & b) {
            return a < b;
        }
        virtual std::string name() {
            return std::string("<");
        }
    };

    template <typename version_type>
    class less_equal : public version_constraint<version_type>
    {
    public:
        virtual bool operator ()(const version_type & a,
                                 const version_type & b) {
            return a <= b;
        }
        virtual std::string name() {
            return std::string("<=");
        }
    };

    template <typename version_type>
    class equal : public version_constraint<version_type>
    {
    public:
        virtual operator () (const version_type & a,
                             const version_type & b) {
            return a == b;
        }
        virtual std::string name() {
            return std::string("==");
        }
    };

    template <typename version_type>
    class matches : public version_constraint<version_type>
    {
    public:
        virtual operator () (const version_type & a,
                             const version_type & b) {
            return a.matches(b);
        }
        virtual std::string name() {
            return std::string("~=");
        }
    };

    template <typename version_type>
    class greater_equal : public version_constraint<version_type>
    {
    public:
        virtual operator () (const version_type & a,
                             const version_type & b) {
            return a >= b;
        }
        virtual std::string name() {
            return std::string(">=");
        }
    };

    template <typename version_type>
    class greater : public version_constraint<version_type>
    {
    public:
        virtual operator () (const version_type & a,
                             const version_type & b) {
            return a > b;
        }
        virtual std::string name() {
            return std::string(">");
        }
    };
}
#endif // UDR_CONSTRAINTS_HPP
