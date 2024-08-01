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
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/dist.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/constant/one.hpp>

namespace eve
{
 template<typename Options>
  struct reldist_t : elementwise_callable<reldist_t, Options,  pedantic_option>
  {
    template<floating_value T,  floating_value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    EVE_FORCEINLINE constexpr common_value_t<T, U> operator()(T a, U b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(reldist_t, reldist_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var reldist
//!   @brief  `elementwise_callable` object computing the relative distance of its arguments.
//!
//!   @groupheader{Header file}
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
//!      // Regular overloads
//!      constexpr auto reldist(floating_value auto x, floating_value auto y)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto reldist[conditional_expr auto c](floating_value auto x, floating_value auto y) noexcept; // 2
//!      constexpr auto reldist[logical_value auto m](floating_value auto x, floating_value auto y)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto reldist[pedantic](floating_value auto x, floating_value auto y)                noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [floating](@ref eve::floating_value) arguments.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of the relative distance of the arguments is returned,  i.e. `eve::abs(x-y)/max(abs(x), abs(y), 1)`.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. `reldist[pedantic](x, y)` computes a distance wich is `NaN` if and only
//!          if one of the parameters is `NaN`.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/reldist.cpp}
//================================================================================================
  inline constexpr auto reldist = functor<reldist_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<value T, callable_options O>
    constexpr T reldist_(EVE_REQUIRES(cpu_), O const& o, T a, T b)
    {
      return dist[o](a, b)/max(abs(a), abs(b), one(as(a)));
    }
  }
}
