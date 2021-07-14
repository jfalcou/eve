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
  //! @var prime_ceil
  //!
  //! @brief Callable object computing the least prime greter or equal to the input.
  //!
  //! **Required header:** `#include <eve/function/prime_ceil.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | unsigned integral prime_ceil   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( unsigned_value auto n ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`n`:   [value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //! The result element type is the same as the input one unless a converter is applied.
  //!
  //! A binary search is performed using nth_prime.
  //!
  //!@warning
  //!    this function will return 0 (or nan) as soon as the input is greater than 104729.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::prime_ceil
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `prime_ceil[cond](x, ...)` is equivalent to `if_else(cond,prime_ceil(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/prime_ceil.cpp
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct prime_ceil_; }

  template<>
  struct supports_optimized_conversion<tag::prime_ceil_> : std::true_type {};

  EVE_MAKE_CALLABLE(prime_ceil_, prime_ceil);
}

#include <eve/module/real/combinatorial/function/regular/generic/prime_ceil.hpp>
