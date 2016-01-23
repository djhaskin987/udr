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
#include "IntegerVersion.hpp"
#include <memory>

UDR::IntegerVersion::IntegerVersion(int val) :
    ver(val)
{ }

UDR::IntegerVersion::~IntegerVersion()
{ }

int UDR::IntegerVersion::compare(const ConstVersionPtr & other) const
{
    const IntegerVersion * other_ptr;
    other_ptr = dynamic_cast<const IntegerVersion*>(other.get());
    if (other_ptr == nullptr)
    {
        throw UDR::VersionMismatchException();
    }

    return (this->ver) - (other_ptr->ver);
}

bool UDR::IntegerVersion::matches(const ConstVersionPtr & other) const
{
    const IntegerVersion * other_ptr;
    if (! (other_ptr =
            dynamic_cast<const IntegerVersion*>(other.get())))
    {
        throw UDR::VersionMismatchException();
    }
    return (other_ptr->ver / 10) == (this->ver / 10);
}

UDR::ConstVersionPtr UDR::IntegerVersion::Create(int val)
{
    return std::unique_ptr<const Version>(
            static_cast<const Version*>(new IntegerVersion(val)));
}

