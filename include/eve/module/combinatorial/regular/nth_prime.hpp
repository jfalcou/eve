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
//!   @var nth_prime
//!   @brief Returns the nth nth_prime number (n < 10000).
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
//!      eve::as_wide_as<M, double> nth_prime(N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  unsigned argument (less than 10000).
//!
//!   **Return value**
//!
//!     the value of the nth nth_prime number is returned.
//!
//!     If the output is of integral type, an incorrect computation will return 0, but
//!     if the result has been converted to a floating value (by modifying
//!     the object function semantic) incorrect computation will return nan
//!
//!     This function will return 0 (or nan) as soon as the correct
//!     result will not be exactly represented in the output type or
//!     (for the current implementation) if n is greater or equal to 10000.
//!
//!   **Notes**
//!
//!     * Almost no computations are made, the results are from a lookup table.
//!       The result element type is the same as the input one unless a converter
//!       is applied to `nth_prime` (see below).
//!
//!     * 2 is the first prime. It is returned for n=0.
//!
//!   **Example**
//!
//!     @godbolt{doc/combinatorial/regular/nth_prime.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Optimized Conversion Call
//!
//!     If the input types are integral, the result is succeptible
//!     not to be representable in the input type. A converter can be applied to choose
//!     the output type and get the correct result.
//!
//!    **Example**
//!
//!      @godbolt{doc/combinatorial/conversion/nth_prime.cpp}
//! @}
//================================================================================================

namespace tag
{
  struct nth_prime_;
}

template<> struct supports_optimized_conversion<tag::nth_prime_> : std::true_type
{};

EVE_MAKE_CALLABLE(nth_prime_, nth_prime);
}

#include <eve/module/combinatorial/regular/impl/nth_prime.hpp>
