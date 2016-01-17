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
// This file is just composed to set up a sample test to make sure that testing
// works.
#ifndef GRIPE_HPP
#define GRIPE_HPP 1



namespace udr {
class Gripe
{
    private:
        int a;
    public:
        Gripe() : a(1) {}
        bool is(int b) {
            return a == b;
        }
};
}
#endif // GRIPE_HPP
