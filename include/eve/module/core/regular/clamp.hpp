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
    template<value T, value U, value V>
    constexpr EVE_FORCEINLINE common_value_t<T, U, V> operator()(T a, U lo, V hi) const noexcept
      requires(eve::same_lanes_or_scalar<T, U, V>)
    {
      EVE_ASSERT(eve::all(lo <= hi), "[eve::clamp] bounds are not correctly ordered");
      return EVE_DISPATCH_CALL_PT((common_value_t<T, U, V>), a, lo, hi);
    }

    EVE_CALLABLE_OBJECT(clamp_t, clamp_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var clamp
//!   @brief `elementwise_callable` clamping the value between two bounds.
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
//!      // Regular overload
//!      constexpr auto clamp(value auto x, value auto lo,  value auto hi)  noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto clamp[conditional_expr auto c](value auto x,
//!                          value auto lo,  value auto hi) noexcept;                // 2
//!      constexpr auto clamp[logical_value auto m](value auto x,
//!                          value auto lo,  value auto hi)    noexcept;             // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: value to clamp.
//!     * `lo`, `hi`: [the boundary values](@ref eve::value) to clamp `x` to.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!        1. Each [element](@ref glossary_elementwise)  of the result contains:
//!           *  `lo`, if `x` is less than `lo`.
//!           *  `hi`, if `hi` is less than `x`.
//!           *  otherwise `x`.
//!        2. [The operation is performed conditionnaly](@ref conditional).
//!
//!   @note
//!     If some lo are not less or equal to the corresponding hi the routine asserts.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/clamp)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/clamp.cpp}
//================================================================================================
  inline constexpr auto clamp = functor<clamp_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr auto clamp_(EVE_REQUIRES(cpu_), O const &, T a, T l, T h) noexcept
    {
      return eve::min(eve::max(a, l), h);
    }
  }
}
