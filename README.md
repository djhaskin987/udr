# udr
Universal Dependency Resolver

This resolves dependencies and downloads packages for a myriad of packaging tools. It's nice to have
it all together.

# Motivation

I got really tired of seeing how often this problem was re-solved over and over every time a new
programming language came out, and every time a new package manager was born. Further,
some of those things only created an (often self-described) half-done solution, something
that *sort of* resolved dependencies, but didn't really. I've also been in situations
where I'm solving a problem as a build engineer and I just need a generic dependency resolver.
So I am building this so that I can use it in my career.

## Why C++?

I seriously considered writing this in a higher-level language than
C++ to write this, especially since its intended audience is build and
DevOps engineers. However, even considering the audience, C++ has some serious
advantages:

1) The library would then have absolutely *no* need for dependencies. Just
   install the package and go. No interpreter, virtual machine,
   or 3rd party library needed.
2) The possibility of having bindings from my library into other
   languages later. It will not matter if an engineer needs to use
   the library in Ruby or Python. The library will support both.
3) Sometimes languages go out of style. In its 30+ years of existence,
   C++ has yet to do this.

# Supported OSes

It is intended that the following OSes with their compilers will be eventually
supported:

OS | Compiler on OS
---|---------------
Windows | msvc2013
Mac | clang
Ubuntu 14.04-16.04 | gcc
CentOS 6-7 | gcc

I will try to make this code build on Windows and Linux, but I'll need
help with the Mac side of things, as I don't own a Mac :(

## Why not just use clang for all OSes?

I like the idea of supporting the most conventional compiler for each OS.
Universal clang support may eventually come, but I'd like to focus on
the compilers listed above for their respective OSes first :)

# How to build

It is intended that the project will use the CMake build process and that
`package` will be one of the targets. Therefore, it should eventually be
possible to build the library with the commands
```
mkdir build
cd build
cmake
[n]make package
```
where `[n]make` is either `nmake` or `make`, depending on if building is
done on Windows or Linux/Mac.

# How to Install

The build process should output a system installer installable for the OS on
which the code was built. This means there will be an `msi` installable on
Windows, an `rpm` on enterprise linux machines, a `deb` on Debian, Ubuntu and
Mint, etc.

# How to Use

There will be a userguide written in asciidoc or LaTeX, and a doxygen-generated
autodocs as well.

# Contribution Guidelines

This project is programmed in C++ using the [C++ Core
Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md),
as, well, guidelines for coding.

All pull requests (PRs) welcome, but subject to whether it's a
good change; however, PRs will rarely be denied if:
- Someone seconds your idea
- The code coverage of any code added by your PR does not fall below 75%
- The code coverage of the project as a whole does not fall below 75%

# Code of Conduct

I strive to maintain an open and safe environment for
contribution. There are a lot of people out there with a lot of
opinions and philosophies.  Therefore, as a rule, any discussion, pull
request, feature request, bug report, or other contribution, made in
part or as a whole with the apparent purpose of talking about,
criticizing, or affecting anything but what the code should be and how
it should behave is at best off topic, and at worst offensive to
somebody. I will listen to complaints at ![this udr abuse email](udr-abuse-email.png) .
I reserve the right to delete any comments or block PRs if those contributions
are hurting someone's feelings through blatant attack or insensitivity.

* Also:
  - Be nice.
  - When someone implements a feature or fixes a bug, please thank them.
  - When a bug or feature has not received attention in a long time, please be
    patient and forgiving.
  - When someone disagrees with you, that's okay.
  - Remember that we are all real people.

Let's all play nice :)
