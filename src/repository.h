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
#ifndef UDR_REPOSITORY_HPP
#define UDR_REPOSITORY_HPP 1

namespace udr {

    class file
    {
        std::string checksum(); // can be NULL
        std::string url();
    }

    class package_constraint
    {
        std::string name() const;
        std::string version() const;
        bool satisfied_by(package) const;
    }

    class repository
    {
        // package name -> (package : file)
        virtual std::map<package, file> lookup_packages(const std::string name) = 0;
    }

    class package
    {
        std::string name() const;
        std::string version() const;
        package_tool * tool() const;
    }

    class package_tool
    {
        typedef ... package_type;
        typedef ... constraint_type;
        typedef ... 

        virtual bool compare_versions(std::string relationship, version, cmpverstring) = 0;
        install
        constraints(file);


}


#endif
