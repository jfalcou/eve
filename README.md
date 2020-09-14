<img src="https://github.com/jfalcou/eve/raw/develop/docs/logo.png" alt="" data-canonical-src="https://github.com/jfalcou/eve/raw/develop/docs/logo.png" align="left"  width="15%" height="15%" />

# EVE - the Expressive Vector Engine

[![CircleCI](https://circleci.com/gh/jfalcou/eve/tree/develop.svg?style=svg&circle-token=341ef01f38a05865882565127a64f692f650fc7b)](https://circleci.com/gh/jfalcou/eve/tree/develop)

## Purpose

EVE is a reimplementation of the old EVE SIMD library by Falcou et al. which for a while was
named Boost.SIMD. It's a C++20 and onward implementation of a type based wrapper around
SIMD extensions sets for most current architectures. It aims at showing how C++20 can be used
to design and implement efficient, low level, high abstraction library suited for high performances.

It's a research project first and an open source library second. We reserve the right to
change API and baseline compiler required until the first official 0.1 release. However, we'll try
to minimize disruption. Semantic versioning will ensure API retro-compatibility if anything huge
needs to change.

## What's left to do?

EVE is roughly usable at the moment but we need to:

- [ ] Complete and host the documentations on the web
- [ ]  Implement algorithms à la std over SIMD-izable ranges
- [ ]  Complete implementations of some functions like multi-register shuffles and some math functions
- [ ] Fix potential performance or codegen issues

## FAQ

 - **Why C++20 ?** Becasue we want to be able to use modern design components like Concepts, and later on, Modules.
 
 - **Why this instead of std::simd or any other libraries?** EVE is a playground for testing proper
 design and implementation decision for such libraries. Vc and its standard version are fine pieces
 of work but we aim at pushing the envelop in term of API and implementation without any standard
 restriction. We will try, however, to keep up with standard naming as much as possible.

 - **Is this Boost.SIMD v42.69?** Yes and no. This reimplementation is based on slightly different
 premises and some radical new ideas. All results exhibited by all our previous Boost.SIMD papers
 still holds and we'll try to improve upon.

 - **I want to help!** Good, we need tests on exotic configuration, maybe a stable PPC test machines.
 Write code, make it fail so we can improve for use cases we may have missed. Fork and hack away.

 ## Papers

 - **Modern Generative Programming for Optimizing Small Matrix-Vector Multiplication**, Jules Penuchot, Joel Falcou, Amal Khabou in *HPCS 2018*
 - **Boost. simd: generic programming for portable simdization**, Pierre Estérie, Joel Falcou, Mathias Gaunard, Jean-Thierry Lapresté, *PACT 2012*
 - **EVE, an object oriented SIMD library**, Joel Falcou, Jocelyn Serot in *Scalable Computing: Practice and Experience 6 (4)*

 ## License

  ```
  MIT License

Copyright (c) 2018-2020 Joel FALCOU
Copyright (c) 2018-2020 Jean-Thierry LAPRESTE

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
