The Expressive Vector Engine
============================

**EVE** is a new implementation of the previous **EVE** SIMD library by Falcou et al. which for a while was named Boost.SIMD. It's a C++20 and onward implementation of a type based wrapper around SIMD extensions sets for most current architectures. It aims at showing how C++20 can be used to design and implement efficient, low level, high abstraction library suited for high performances.

It's a research project first and an open source library second. We reserve the right to change API and baseline compiler required until the first official 0.1 release. However, we'll try to minimize disruption. Semantic versioning will ensure API retro-compatibility if anything huge needs to change.

# Bibliographic References

If you want to refers to **EVE**, you can currently use those papers (by order of preference in citation).
A new, more up-to-date **EVE** specific journal paper is in the work atm.

 - [**Modern Generative Programming for Optimizing Small Matrix-Vector Multiplication**, Jules Penuchot, Joel Falcou, Amal Khabou in *HPCS 2018*](https://hal.archives-ouvertes.fr/hal-01409286/document)
 - [**Boost. simd: generic programming for portable simdization**, Pierre Estérie, Joel Falcou, Mathias Gaunard, Jean-Thierry Lapresté, *PACT 2012*](https://core.ac.uk/download/pdf/51214382.pdf#page=110)
 - [**EVE, an object oriented SIMD library**, Joel Falcou, Jocelyn Serot in *Scalable Computing: Practice and Experience 6 (4)*](https://www.scpe.org/index.php/scpe/article/download/345/32)
