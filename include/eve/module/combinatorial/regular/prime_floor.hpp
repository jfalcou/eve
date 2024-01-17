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
  struct prime_floor_t : elementwise_callable<prime_floor_t, Options>
  {
    template<eve::unsigned_value T>
    EVE_FORCEINLINE
    T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(prime_floor_t, prime_floor_);
  };

//================================================================================================
//! @addtogroup combinatorial
//! @{
//!   @var prime_floor
//!   @brief Returns the the greatest prime less or equal to the input.
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
//!      N prime_floor(N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  unsigned argument. If `n` is greater than 104'729, behavior is undefined.
//!
//!   **Return value**
//!   The greatest prime less or equal to `n`.
//!   The result type is the same as the input one unless a converter is applied (see below).
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/combinatorial/regular/prime_floor.cpp}
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
//!    @godbolt{doc/combinatorial/conversion/prime_floor.cpp}
//! @}
//================================================================================================
inline constexpr auto prime_floor = functor<prime_floor_t>;
}

#include <eve/module/combinatorial/regular/impl/prime_floor.hpp>
