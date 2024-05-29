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
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/all.hpp>

namespace eve
{

  template<typename Options>
  struct clamp_t : elementwise_callable<clamp_t, Options>
  {
    template<value T,  value U,  value V>
    requires(eve::same_lanes_or_scalar<T, U, V>)
    constexpr EVE_FORCEINLINE common_value_t<T, U, V>
    operator()(T a, U lo, V hi) const noexcept
    {
      EVE_ASSERT(eve::all(lo <= hi), "[eve::clamp] bounds are not correctly ordered");
      return EVE_DISPATCH_CALL(a, lo, hi);
    }

    EVE_CALLABLE_OBJECT(clamp_t, clamp_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var clamp
//!   @brief Computes the largest integer not greater than the input.
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
//!      template< eve::value T, eve::value U,  eve::value V>
//!      auto clamp(T x, U lo, V hi) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` : value to clamp.
//!
//!     * `lo`, `hi`: [the boundary values](@ref eve::value) to clamp `x` to.
//!
//!    **Return value**
//!      Each [element](@ref glossary_elementwise)  of the result contains:
//!          *  `lo`, if `x` is less than `lo`.
//!          *  `hi`, if `hi` is less than `x`.
//!          *  otherwise `x`.
//!
//!      If some lo are not less than the corresponding hi the routine asserts.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/clamp.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::clamp[mask](x, ...)` provides a masked version of `eve::clamp` which is
//!     equivalent to `if_else (mask, clamp(x, ...), x)`.
//!
//! @}
//================================================================================================
  inline constexpr auto clamp = functor<clamp_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto clamp_(EVE_REQUIRES(cpu_), O const &, T a, T l, T h) noexcept
    {
      return eve::min(eve::max(a, l), h);
    }
  }
}
