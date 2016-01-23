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
#ifndef UDR_VERSION_HPP
#define UDR_VERSION_HPP 1

namespace UDR
{
    class Version;
    using std::unique_ptr<Version> = VersionPtr;
    using std::unique_ptr<const Version> = ConstVersionPtr;

    class Version
    {
        public:

            // needed?
            //virtual std::unique_ptr<Version*> clone() = 0;

            Version(const Version&) = delete;
            Version& operator=(const Version&) = delete;

            virtual ~Version() = 0;

            virtual int compare(const ConstVersionPtr & other) const = 0;
            virtual bool match(const ConstVersionPtr & other) const = 0;
    };
}

#endif
