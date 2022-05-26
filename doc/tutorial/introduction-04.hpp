#error This file is for documentation only - DO NOT INCLUDE
/**

@page intro-04 Data Structures

In the previous tutorial, we laid out how **EVE** can use SIMD-aware tuples to handle more complex
cases. In this tutorial, we'll go over how we can design semantically equivalent user-defined types.

# Adapting UDT to SIMD processing
Using tuples as a random bag of values returned from functions is somewhat lackluster. Indeed, one
would prefer names over field numbers, thus rising the level of abstraction.

Following this trend, we can rewrite our scalar `to_polar` function to return a proper structure.

@snippet tutorial/intro-04.cpp scalar-udt

The next thing we want is to be able to write `eve::wide<polar_coords>` and have everything we
already put in place for handling tuple just works with user-defined type. **EVE** provides
an opt-in system to do just that.

To register `polar_coords` to be usable as a type inside eve::wide, two things are needed:
  - adapt the structure to be [compatible with C++ structured bindings](https://en.cppreference.com/w/cpp/language/structured_binding).
    This includes specializations for `std::tuple_size`, `std::tuple_element` and a `get` function.
  - specialize eve::is_product_type to opt-in for product-type behavior

@snippet tutorial/intro-04.cpp simd-udt-adapt

The most interesting effect of this adaptation protocol is that you can adapt pre-existing
user defined types without modifying their code, thus allowing for 3rd party types adaptations.

We can then just rewrite `to_polar` to use this new UDT.

@snippet tutorial/intro-04.cpp simd-udt-to_polar

Note how the semantic improved by being able to explicitly states we return a SIMD register made
of instance of `polar_coords`.

# Creating SIMD-aware UDT
All this boilerplate can be overwhelming so instead of adapting existing code, you may want to build
a new user-defined type directly usable as a SIMD type. **EVE** provides an intrusive protocol
to do just that via the use of the eve::struct_support helper.

@snippet tutorial/intro-04.cpp simd-udt-create

Let's go over the new components introduced here:

  - eve::struct_support is to be used as a base class for the new user-defined type. It acts as
    a [CRTP](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern) base class that
    gathers the ordered list of the desired members types. Here we want `udt::polar_coords` to be
    two `float`s. Said data members will then be automatically stored by eve::struct_support and
    accessible via a tuple-like interface via `get`.

  - By default, inheriting from eve::struct_support provides overloads for equality and inequality
    operators.

  - `using eve_disable_ordering = void;` is an opt-out for the otherwise automatically generated
    comparison operators as we don't want to automatically be able to order instances of `polar_coords`.

  - We then define friend functions to assign names to numbered fields. As the
    structure thus defined will be usable in both scalar and SIMD context, we use the eve::like
    concept to overload them. `eve::like<polar_coords>` used as a parameters concept means that the
    function accepts any type that behaves like a `polar_coords`, i.e `polar_coords` and
    `eve::wide<polar_coords>`. Such function can also be defined as regular function, but this form
    is easier and safer.

This is the bare minimum we can do with eve::struct_support. Additional operators can be added along
with stream insertion. Check eve::struct_support documentation for more informations.

# Storage and Processing
The last step in this situation is now to process multiples `udt::polar_coords` using algorithms.
The most efficient way to do so is to use eve::soa_vector as a container for SIMD-aware types, either
adapted or created using eve::struct_support.

eve::soa_vector provides a `std::vector`-like interface but perform automatic Structure of Array
storage optimisation, ensures the best alignment possible for each sub-members and is directly usable
as **EVE** algorithm input or output.

Let's see how eve::soa_vector can be used as a proper output parameter for out `to_polar` function.

@snippet tutorial/intro-04.cpp simd-soa_vector_out

Now, as a final example, let's a do a `cartesian_coords` SIMD user-defined type and write
`to_cartesian`.

@snippet tutorial/intro-04.cpp simd-soa_vector_in

# Conclusion
In this tutorial, we managed to:
  - adapt existing UDT to be compatible with eve::wide
  - create new UDTs compatible with eve::wide by constrcution
  - use eve::soa_vector, the SIMD-aware storage in place of standard containers
  - process SIMD-aware storage with **EVE** algorithms

**/
