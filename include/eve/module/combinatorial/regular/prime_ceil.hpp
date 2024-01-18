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
  struct prime_ceil_t : elementwise_callable<prime_ceil_t, Options>
  {
    template<eve::unsigned_value T>
    constexpr EVE_FORCEINLINE
    T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(prime_ceil_t, prime_ceil_);
  };

//================================================================================================
//! @addtogroup combinatorial
//! @{
//!   @var prime_ceil
//!   @brief Returns the smallest prime greater or equal to the input.
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
//!      N prime_ceil(N n) ;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  unsigned argument. If `n` is greater than 104'729, behavior is undefined.
//!
//!   **Return value**
//!   The smallest prime greater or equal to `n`.
//!   The result type is the same as the input one unless a converter is applied (see below).
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/combinatorial/regular/prime_ceil.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Optimized Conversion Call
//!
//!     The converters eve::float_,  eve::double_, eve::floating_ can be applied to
//!     produce a floating point output.
//!
//!    **Example**
//!
//!    @godbolt{doc/combinatorial/conversion/prime_ceil.cpp}
//! @}
//================================================================================================
inline constexpr auto prime_ceil = functor<prime_ceil_t>;
}

#include <eve/module/combinatorial/regular/impl/prime_ceil.hpp>
