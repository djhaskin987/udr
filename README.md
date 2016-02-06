# udr
Universal Dependency Resolver

This resolves dependencies and downloads packages for a myriad of packaging tools. It's nice to have
it all together.

# Motivation

I got really tired of seeing how often this problem was re-solved over and over
every time a new programming language came out, and every time a new package
manager was born. Further, some of those things only created an (often
self-described) half-done solution, something that *sort of* resolved
dependencies, but didn't really. I've also been in situations where I'm solving
a problem as a DevOps engineer and I just need a generic dependency resolver
that I can use in a specific environment.  I started building this so that I
can use it in my career and I hope it may be helpful to others, too.

# Philosophy

Ultimately, I want a dependency resolver that just *works*. Taking cues from
the coded package repository, the core resolver will find the first solution
available using the most "preferred" packages first as returned by the
repository.  The resolver may sacrifice speed for correctness, but generally a
few seconds longer in a build is far better than a failed dependency
resolution.

## Why C++?

I seriously considered writing this in a language higher-level C++, especially
since it doesn't need to be lightning fast or multi-threaded, and others who
might be interested in developing a DevOps tool would probably prefer a higher
level language. However, for DevOps engineers, the intended users of the tool,
writing the tool in C++ has some serious advantages:

1) The library would then have little need for dependencies. Just
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

I will try to make this code build on Linux first, then Windows, but I'll need
help with the Mac side of things, as I don't own a Mac :(

## What about clang?

If you want to help with this, I will *totally* accept your PR. Just have a
look at [CONTRIBUTING.md](CONTRIBUTING.md) and [CODE\_OF\_CONDUCT.md](CODE\_OF\_CONDUCT.md) :)

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

The build process should eventually output a system installer installable for the OS on
which the code was built. This means there will be an `msi` installable on
Windows, an `rpm` on enterprise linux machines, a `deb` on Debian, Ubuntu and
Mint, etc.

# How to Use

There will be a userguide written in asciidoc or LaTeX, and a doxygen-generated
autodocs as well.

