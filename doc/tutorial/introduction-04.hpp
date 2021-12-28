#error This file is for documentation only - DO NOT INCLUDE
/**

@page intro-04 SIMD Data Structures

@tableofcontents

In the previous tutorial, we laid out how **EVE** can use SIMD-aware tuple to handle more complex
cases. In this tutorial, we'll go over how we can design semantic-rich user-defined types to do the
same.

@snippet tutorial/intro-04.cpp  empty

## Adapting UDT to SIMD processing
Using tuples as a random bag of values returned from functions is sometime lackluster. Indeed, one
may need to return data structure with proper semantic or which members have a proper semantic.
User-defined types with named members is then preferred.

Following this trend, we can rewrite our scalar `to_polar` function to return a proper structure.

@snippet tutorial/intro-04.cpp scalar-udt

The next thing we want is to be able to write `eve::wide<polar_coords>` and have everything we
already put in place for handling tuple just works with user-defined type. **EVE** provides
an opt-in system to do just that.

To register `polar_coords` to be usable as a type inside eve::wide, two things are needed:
  - adapt the structure to be compatible with C++ structured bindings. This includes providing
    specializations for `std::tuple_size`, `std::tuple_element` and a RAII accessible `get` function.
  - specialize eve::is_product_type to opt-in for product-type behavior

@snippet tutorial/intro-04.cpp simd-udt-adapt

The most interesting effect of this adaptation protocol is that you can adapt pre-existing
user defined types without modifying their code, thus allowing for 3rd party types adaptations.

We can then just rewrite `to_polar` to use this new UDT.

@snippet tutorial/intro-04.cpp simd-udt-to_polar-new

Note how the semantic improved by being able to explicitly states we return a SIMD register made
of instance of `polar_coords`.

## Creating SIMD-aware UDT
Sometimes however, you may want to do a bit more than just adapting types. You may want to build
a new user-defined type directly usable as a SIMD type. **EVE** provides an intrusive protocol
to do just that via the use of the eve::struct_support helper.

@snippet tutorial/intro-04.cpp simd-udt-create

Again, we can then just rewrite `to_polar` to use this new UDT.

@snippet tutorial/intro-04.cpp simd-udt-to_polar-new

## Storage and Processing


## Conclusion
In this tutorial, we managed to:
  - adapt existing UDT to be compatible with eve::wide
  - create new UDTs compatible with eve::wide by constrcution
  - use SIMD-aware storage in place of standard containers
  - process SIMD-aware storage with **EVE** algorithms

**/
