//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
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
  //! @brief Callable object performing the computation the nth prime integer.
  //!
  //! **Required header:** #include <eve/module/combinatorial.hpp>
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | unsigned integral nth_prime   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< unsigned_value T > auto operator()( T n ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`n`:   [unsigned value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //! The result element type is the same as the input one unless a converter is applied to `nth_prime`.
  //! See the example below.
  //!
  //! Almost no computations are made, the results are from a lookup table.
  //!
  //! 2 is the first prime number (n=0). If the output is of integral type incorrect computation will return 0, but
  //! if the result has been converted to a floating value (by concerting the object function) incorrect computation will return nan
  //!
  //!@warning
  //!    this function will return 0 (or nan) as soon as the correct result will not be exactly represented
  //!    in the output type or (for the current impl/ementation) if n is greater or equal to 10000.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/combinatorial/nth_prime.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct nth_prime_; }

  template<>
  struct supports_optimized_conversion<tag::nth_prime_> : std::true_type {};

  EVE_MAKE_CALLABLE(nth_prime_, nth_prime);
}

#include <eve/module/combinatorial/regular/impl/nth_prime.hpp>
