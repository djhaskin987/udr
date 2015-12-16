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
#include <list>
#include <algorithm>
#include <string>


struct constraint
{
    std::string version;
    std::string constraint;
};

struct file
{
    std::string url;
    std::string checksum;
};

// this is a concrete class.
class package_behavior_profile
{
private:
    std::function<bool(std::string)> validate_name;
    std::function<bool(std::string)> validate_version;
    std::function<int(std::string,std::string)> compare_versions;
    std::function<bool(constraint)> validate_constraint;
    std::function<bool(constraint,std::string)> check_constraint;
public:
    const std::function<bool(std::string)> validate_name() {
        return validate_name;
    }
    const std::function<bool(std::string)> validate_version() {
        return validate_version;
    }
    const std::function<int(std::string,std::string)> compare_versions() {
        return compare_versions;
    }
    const std::function<bool(std::string)> satisfies(constraint c) {
        return [this->check_constraint,c](std::string ver) {
            return this->check_constraint(c, ver);
        };
    }
};

class respository {
private:
    package_behavior_profile package_behavior;
    std::function<std::map<version,file>(const std::string &)> query;
    std::function<std::map<name, std::list<constraint>(const std::string &, const std::string &) > query_dependencies;
public:
    std::list<file> resolve(const std::map<name, std::list<constraint> > order) {

    std::list<file> returned;
    for (auto package : order) {
        std::string name = package.first;
        std::list<constraint> constraints = package.second;
        std::map<version, file> candidates = this->query(name);

        for (auto constraint : constraints) {
            std::remove_if(candidates.begin(), candidates.end(),
                    this->package_behavior.satisfies(constraint))
        }

        if (candidates.empty() ) {
            return returned;
        }

        candidates = sort(candidates,
            []{ return -1 * this->package_behavior.compare_versions(); } );

        for (auto candidate : candidates) {
            auto candidate_version = candidate.first;
            auto candidate_file = candidate.second;
            auto candidate_deps =
                this->query_dependencies(name, candidate_version);
            auto candidate_dep_files = this->resolve(candidate_deps);
            if (!candidate_dep_files.empty()) {
                // concatenate lists, use move semantics if possible
                returned = returned + candidate_dep_files;

                returned.push_back(candidate_file);
                break;
            }
        }
    }
    }
};
#endif // UDR_REPOSITORY_HPP
