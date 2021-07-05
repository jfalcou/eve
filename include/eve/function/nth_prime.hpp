//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup combinatorial
  //! @{
  //! @var nth_prime
  //!
  //! @brief Callable object performing the computation of unsigned integral nth_prime.
  //!
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/nth_prime.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | unsigned integral nth_prime   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< unsigned_value T > auto operator()( T n ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`n`:   [value](../../concepts.html#value).
  //!
  //!
  //!
  //! **Return value**
  //!
  //!
  //! The result element type is the same as the input one unless a converter is applied to `nth_prime`.
  //! See the example below.
  //!
  //!
  //! Almost no computations are made, the results are from a lookup table.
  //!
  //! 2 is the first prime number (n=0). If the output is of integral type incorrect computation will return 0, but
  //! if the result has been converted to a floating value (by concerting the object function) incorrect computation will return nan
  //!
  //!@warning
  //!    this function will return 0 (or nan) as soon as the correct result will not be exactly represented
  //!    in the output type or (for the current implementation) if n is greater or equal to 10000.
  //!
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::nth_prime
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `nth_prime[cond](x, ...)` is equivalent to `if_else(cond,nth_prime(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  decorators NOT FOUND
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/nth_prime.cpp
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct nth_prime_; }

  template<>
  struct supports_optimized_conversion<tag::nth_prime_> : std::true_type {};

  EVE_MAKE_CALLABLE(nth_prime_, nth_prime);
}

#include <eve/module/real/combinatorial/function/regular/generic/nth_prime.hpp>
