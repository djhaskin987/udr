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
#include "StringName.hpp"

UDR::StringName::StringName(const std::string & name) : name(name)
{ }

std::string UDR::StringName::getName() const
{
    return name;
}


bool UDR::StringName::equals(const ConstNamePtr & other) const
{
    return false;
}


UDR::ConstNamePtr UDR::StringName::Create(const std::string & name)
{
    return std::unique_ptr<const Name>(
            static_cast<const Name*>(new StringName(name)));
}

