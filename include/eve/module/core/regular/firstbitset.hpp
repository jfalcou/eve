//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/bit_andnot.hpp>

namespace eve
{
  template<typename Options>
  struct firstbitset_t : elementwise_callable<firstbitset_t, Options>
  {
    template<eve::integral_value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const
    { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(firstbitset_t, firstbitset_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var firstbitset
//!   @brief Computes [elementwise](@ref glossary_elementwise) the bit pattern
//!   in which the only bit set (if it exists) is the first bit set in the input.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::unsigned_value T >
//!      T firstbitset(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!       Computes [elementwise](@ref glossary_elementwise) the bit pattern in
//!       which the only bit set (if it exists) is
//!       the first bit set (beginning with the least significant bit) in the input.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/firstbitset.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::firstbitset[mask](x)` provides a masked
//!     version of `firstbitset` which is
//!     equivalent to `if_else(mask, firstbitset(x), x)`
//!
//! @}
//================================================================================================
  inline constexpr auto firstbitset = functor<firstbitset_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    firstbitset_(EVE_REQUIRES(cpu_), O const &, T a0) noexcept
    {
      return a0 & inc(~a0);
    }
  }
}
