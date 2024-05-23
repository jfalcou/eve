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
#include <eve/module/core/regular/round.hpp>

namespace eve
{
  template<typename Options>
  struct significants_t : strict_elementwise_callable<significants_t, Options, upward_option, downward_option,
                                                      to_nearest_option, toward_zero_option>
  {
    template<floating_value T0, value T1>
    EVE_FORCEINLINE constexpr as_wide_as_t<T0, T1> operator()(T0 t0, T1 n) const noexcept
    {
      EVE_ASSERT(n >= 0 && n < 16, "[eve::fracscale] -  integral scale out of range [0, 15]: " << n);
      return EVE_DISPATCH_CALL(t0, n);
    }

    template<floating_value T0, auto N>
    EVE_FORCEINLINE constexpr as_wide_as_t<T0> operator()(T0 t0, index_t<N> const &) const noexcept
    {
      EVE_ASSERT(N >= 0 && N < 16, "[eve::fracscale] -  scale integral constant out of range [0, 15]: " << N);
      return EVE_DISPATCH_CALL(t0, n);
    }

    EVE_CALLABLE_OBJECT(significants_t, significants_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var fracscale
//!   @brief Computes the reduced part of the scaled input.
//!
//!   The call is equivalent to `a0-roundscale(a0,scale)`
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
//!      template< eve::floating_value T, int scale >
//!      T fracscale(T x, int scale) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      * `x`:      [real floating value](@ref eve::floating_value).
//!      * `scale` : int or std::integral_constant of int type limited to the range [0, 15].
//!
//!    **Return value**
//!
//!      Returns the [elementwise](@ref glossary_elementwise) reduced part of the scaled input.
//!      The number of fraction bits retained is specified by scale. By default the internal
//!      rounding after scaling is done to nearest integer.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/fracscale.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::fracscale[mask](x, scale)` provides a masked version of `eve::fracscale`
//!     which is equivalent to `if_else (mask, eve::fracscale(x, scale), x)`.
//!
//!   * eve::to_nearest, eve::toward_zero, eve::upward,  eve::downward
//!
//!     If d is one of these 4 decorators
//!     The call `d(eve:fracscale)(x, scale)`, call is equivalent to  `a0-d(eve::roundscale)(a0, scale)`
//!
//! @}
//================================================================================================
  inline constexpr auto fracscale = functor<fracscale_t>;
}

#include <eve/module/core/regular/impl/fracscale.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fracscale.hpp>
#endif
