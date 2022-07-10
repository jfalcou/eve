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
  //!   @var prime_ceil
  //!   @brief Returns the the least prime greater or equal to the input.
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/combinatorial.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::unsigned_value N >
  //!      N prime_ceil(N n) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `n` :  unsigned argument.
  //!
  //!   **Return value**
  //!
  //!     The result element type is the same as the input one unless a converter
  //!     is applied (see below).
  //!
  //!     @warning
  //!       this function will return 0 (or nan, see below) as soon as the input is greater than 104729.
  //!
  //!   **Example**
  //!
  //!     @godbolt{doc/combinatorial/regular/prime_ceil.cpp}
  //!
  //!  @groupheader{Semantic Modyfiers}
  //!
  //!   * Optimized Conversion Call
  //!
  //!     The converters eve::float_,  eve::double_, eve::floating_ can be applied to
  //!     produce a floating point output.
  //!
  //!    **Example**
  //!
  //!      @godbolt{doc/combinatorial/conversion/prime_ceil.cpp}
  //! @}
  //================================================================================================
  namespace tag { struct prime_ceil_; }

  template<>
  struct supports_optimized_conversion<tag::prime_ceil_> : std::true_type {};

  EVE_MAKE_CALLABLE(prime_ceil_, prime_ceil);
}

#include <eve/module/combinatorial/regular/impl/prime_ceil.hpp>
