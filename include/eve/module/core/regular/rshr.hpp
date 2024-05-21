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
#include <eve/detail/assert_utils.hpp>

namespace eve
{
  template<typename Options>
  struct rshr_t : strict_elementwise_callable<rshr_t, Options>
  {
    template<unsigned_value T, integral_value N>
    EVE_FORCEINLINE constexpr auto/*as_wide_as_t<T, N>*/ operator()(T t0, N s) const noexcept
    {
      EVE_ASSERT(detail::assert_good_shift<T>(s),
                 "[eve::rshr] - Shifting by " << s << " is out of the range ]"
                 << -int(sizeof(element_type_t<T>) * 8) << ", "
                 << sizeof(element_type_t<T>) * 8 << "[.");
      return EVE_DISPATCH_CALL(t0, s);
    }

    template<unsigned_value T, std::ptrdiff_t S>
    EVE_FORCEINLINE constexpr T operator()(T t0, index_t<S> s) const noexcept
    {
      EVE_ASSERT(detail::assert_good_shift<T>(S),
                 "[eve::rshr] - Shifting by " << S << " is out of the range ]"
                 << -int(sizeof(element_type_t<T>) * 8) << ", "
                 << sizeof(element_type_t<T>) * 8 << "[.");
      return EVE_DISPATCH_CALL(t0, s);
    }

    EVE_CALLABLE_OBJECT(rshr_t, rshr_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var rshr
//!   @brief Computes the arithmetic right/left shift operation according to shift sign.
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
//!      template< eve::unsigned_value T , integral_value N >
//!      T rshr(T x, N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::ordered_value) to be shifted.
//!     * `n`:    [shift](@ref eve::integral_value).
//!
//!    **Return value**
//!
//!      The value of the arithmetic right/left shift operation according to shift
//!      sign is returned
//!
//!   @note
//!     *  the call `rshr(x, n)` is equivalent to `if_else(n>0, shl(x, n), shr(x, n))`
//!        if `x`  is an  [simd value](@ref eve::simd_value).
//!
//!     *  The types must share the same cardinal or be scalar and if `N`
//!        is the size in bits  of the element type of `T`, all
//!        [elements](@ref glossary_elementwise) of n must belong to the
//!        interval: `]-N, N[` or the result is undefined.
//!
//!     * The call `rshr(x, n)` is equivalent to `x << n` if `x`  is
//!       an [simd value](@ref eve::simd_value).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/rshr.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::rshr[mask](x, ...)` provides a masked
//!     version of `rshr` which is
//!     equivalent to `if_else(mask, rshr(x, ...), x)`
//!
//! @}
//================================================================================================
  inline constexpr auto rshr = functor<rshr_t>;
}
#  include <eve/module/core/regular/impl/rshr.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/rshr.hpp>
#endif
