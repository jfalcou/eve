<img src="https://github.com/jfalcou/eve/raw/main/doc/logo.png" alt="" data-canonical-src="https://github.com/jfalcou/eve/raw/main/doc/logo.png" align="left"  width="15%" height="15%" />

# EVE - the Expressive Vector Engine

[![E.V.E CI](https://github.com/jfalcou/eve/actions/workflows/main.yml/badge.svg)](https://github.com/jfalcou/eve/actions/workflows/main.yml)
[![Licence](https://img.shields.io/github/license/jfalcou/eve?style=plastic)](https://img.shields.io/github/license/jfalcou/eve?style=plastic)
[![Discord](https://img.shields.io/discord/692734675726237696?style=plastic)](https://discord.gg/8A4Q4HkhcW)

## Purpose

EVE is a reimplementation of the old EVE SIMD library by Falcou et al. which for a while was
named Boost.SIMD. It's a C++20 and onward implementation of a type based wrapper around
SIMD extensions sets for most current architectures. It aims at showing how C++20 can be used
to design and implement efficient, low level, high abstraction library suited for high performances.

It's a research project first and an open source library second. We reserve the right to
change API and baseline compiler required until the first official 0.1 release. However, we'll try
to minimize disruption. Semantic versioning will ensure API retro-compatibility if anything huge
needs to change.

## Getting Started

 - [Installing and using the library](https://jfalcou.github.io/eve/install.html)
 - [Fetching EVE using your favorite Package Manager](https://jfalcou.github.io/eve/packages.html)
 - [Your first SIMD code using EVE](https://jfalcou.github.io/eve/simd-101.html)
 - [References Documentation](https://jfalcou.github.io/eve/modules.html)

## Video materials

### SIMD in C++20: EVE of a new Era - CppCon 2021

[![SIMD in C++20: EVE of a new Era - CppCon 2021](http://img.youtube.com/vi/WZGNCPBMInI/0.jpg)](http://www.youtube.com/watch?v=WZGNCPBMInI "Video Title")

### SIMD Algorithms Design

[![Playlist by Denis Yaroshevskiy](http://img.youtube.com/vi/U1e_k8xmwR0/0.jpg)](https://www.youtube.com/playlist?list=PLYCMvilhmuPEM8DUvY6Wg_jaSFHpmlSBD)

## Current status - Operationnal

EVE is considered **operationnal**: it's usable, has a large feature sets for a sensible amount of instructions sets but it's possible some values or performances issues may still remain. Don't hesitate to report any funky code-gen or bad optimizations so we can deliver the best performance around.

### Current roster of supported Instructions Sets

Full support with tests:
 - **Intel**
   - SSE2, SSSE3, SSE3, SSE4.1, SSE4.2
   - AVX, AVX2, FMA3
   - AVX512 Skymake style (F,CD,DQ,BW,VL)
 - **ARM**
   - NEON (64 & 128 bits)
   - AARCH64

Partial/In-progress support with minimal checks:
 - **PowerPC**
   - VMX
   - VSX

 - We **do not support** ARM SVE as the execution model makes no sense and the current compiler support is not adequate for us.
 - We **do not support** GPGPU, this is the job for another tool.

### Current roster of supported compiler

EVE requires a C++ 20 compliant compiler. The main features from C++17/20 we require are:
 - Concepts and requires
 - Template lambdas
 - Inline variables
 - Non-Type Template Parameters
 - `if constexpr`
 - Functions from `<bits>`

Here is the current minimal compiler version supported:

| Compiler       | Version       |
| -------------- | ------------- |
| g++            | 11 or above   |
| clang++        | 13 or above   |
| Visual Studio  | *TBD*         |

Visual Studio support is currently being added. Help on the front of setting up appveyor properly is also welcome.

## FAQ

 - **Why C++20 ?** Because we want to be able to use modern design components like Concepts, and later on, Modules. C++14 is for 2014.
   We fully know it may hinders adoption in some situation, but we're not running a race. We value proper design and API choice over
   complex retro-compatibility.

 - **Why this instead of std::simd or any other libraries?** EVE is a playground for testing proper
   design and implementation decisions for such libraries. Vc and its standard version are fine pieces
   of work but we aim at pushing the envelope in term of API and implementation without any standard
   restriction. We will try, however, to keep up with standard naming as much as possible.

 - **Is this Boost.SIMD v42.69?** Yes and no. This reimplementation is based on slightly different
   premises and some radical new ideas. All results exhibited by all our previous Boost.SIMD papers
   still hold and we'll try to improve upon.

 - **I want to help!** Good, we need tests on exotic configuration, maybe a stable PPC test machine.
   Write code, make it fail so we can improve for use cases we may have missed. Fork and hack away.
   We would also value input (even harsh ones) on how we use our CI infrastructure or how our CMake looks.
   We tried our best but those elements are complex all by themselves.

## Bibliographic References

If you want to refer to EVE, you can currently use those papers (by order of preference in citation).
A new, more up-to-date EVE specific journal paper is in the work atm.

 - **Modern Generative Programming for Optimizing Small Matrix-Vector Multiplication**, Jules Penuchot, Joel Falcou, Amal Khabou in *HPCS 2018*
 - **Boost. simd: generic programming for portable simdization**, Pierre Estérie, Joel Falcou, Mathias Gaunard, Jean-Thierry Lapresté, *PACT 2012*
 - **EVE, an object oriented SIMD library**, Joel Falcou, Jocelyn Serot in *Scalable Computing: Practice and Experience 6 (4)*

 ## License

```
MIT License

Copyright : EVE Contributors & Maintainers

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
