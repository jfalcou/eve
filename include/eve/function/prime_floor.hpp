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
  //! @var prime_floor
  //!
  //! @brief Callable object computing the greater prime integer less or equal to the input.
  //!
  //! **Required header:** `#include <eve/function/prime_floor.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | unsigned integral prime_floor   |
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
  //!`n`:   [value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //! The result element type is the same as the input one unless a converter is applied.
  //!
  //! A binary search is performed using nth_prime.
  //!
  //!@warning
  //!    this function will return 0 (or nan) as soon as the input is greater than 104729 or less than 2.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::prime_floor
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `prime_floor[cond](x, ...)` is equivalent to `if_else(cond,prime_floor(x, ...),x)`
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
  //! @include{lineno} doc/core/prime_floor.cpp
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct prime_floor_; }

  template<>
  struct supports_optimized_conversion<tag::prime_floor_> : std::true_type {};

  EVE_MAKE_CALLABLE(prime_floor_, prime_floor);
}

#include <eve/module/real/combinatorial/function/regular/generic/prime_floor.hpp>
