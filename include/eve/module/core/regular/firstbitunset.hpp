//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/bit_notand.hpp>

namespace eve
{
  template<typename Options>
  struct firstbitunset_t : elementwise_callable<firstbitunset_t, Options>
  {
    template<eve::integral_value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const
    { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(firstbitunset_t, firstbitunset_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var firstbitunset
//!   @brief Computes [elementwise](@ref glossary_elementwise) the bit pattern
//!   in which the only bit set (if it exists) is the first bit unset in the input.
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
//!      T firstbitunset(T x) noexcept;
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
//!       the first bit unset (beginning with the least significant bit) in the input.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/firstbitunset.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::firstbitunset[mask](x)` provides a masked
//!     version of `firstbitunset` which is
//!     equivalent to `if_else(mask, firstbitunset(x), x)`
//!
//! @}
//================================================================================================
  inline constexpr auto firstbitunset = functor<firstbitunset_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    firstbitunset_(EVE_REQUIRES(cpu_), O const &, T a0) noexcept
    {
      return     if constexpr( scalar_value<T> )
        return ~a0 & inc(a0);
      else
        return bit_notand(a0, inc(a0));
    }
  }
}
