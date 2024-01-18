//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct nth_prime_t : elementwise_callable<nth_prime_t, Options/*, upgrade_converter_option*/>
  {
    template<eve::unsigned_value T>
    constexpr EVE_FORCEINLINE
    T operator()(T v) const  noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(nth_prime_t, nth_prime_);
  };

//================================================================================================
//! @addtogroup combinatorial
//! @{
//!   @var nth_prime
//!   @brief Returns the nth prime number.
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
//!      eve::as_wide_as< double, N > nth_prime(N n) ;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` : unsigned argument. If n is greater than 10'000, behavior is undefined.
//!
//!   **Return value**
//!
//!     The value of the nth prime number is returned.
//!
//!   **Notes**
//!
//!     * 2 is the first prime. It is returned for n=0.
//!
//!     * Almost no computations are made, the results are from a lookup table.
//!       The result element type is the same as the input one unless a converter
//!       is applied to eve::nth_prime (see below).
//!
//!   **Example**
//!
//!     @godbolt{doc/combinatorial/regular/nth_prime.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Optimized Conversion Call
//!
//!     If the input types are integral, the result is susceptible not to be representable in the
//!     input type. A converter can be applied to choose the output type and get the correct result.
//!
//!    **Example**
//!
//!      @godbolt{doc/combinatorial/conversion/nth_prime.cpp}
//! @}
//================================================================================================
inline constexpr auto nth_prime = functor<nth_prime_t>;

}

#include <eve/module/combinatorial/regular/impl/nth_prime.hpp>
