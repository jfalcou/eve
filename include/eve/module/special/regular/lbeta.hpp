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
#include <eve/module/special/regular/log_abs_gamma.hpp>
#include <eve/traits/common_value.hpp>

namespace eve
{
template<typename Options>
struct lbeta_t : elementwise_callable<lbeta_t, Options>
{
  template<eve::floating_value T0, eve::floating_value T1>
  requires (same_lanes_or_scalar<T0, T1>)
  EVE_FORCEINLINE constexpr
  eve::common_value_t<T0, T1> operator()(T0 a, T1 b) const  noexcept
  { return EVE_DISPATCH_CALL(a, b); }

  EVE_CALLABLE_OBJECT(lbeta_t, lbeta_);
};

//================================================================================================
//! @addtogroup special
//! @{
//!   @var lbeta
//!   @brief `elementwise_callable` object computing the natural logarithm of the beta function.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto lbeta(floating_value auto x, floating_value auto y)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto lbeta[conditional_expr auto c](floating_value auto x, floating_value auto y) noexcept; // 2
//!      constexpr auto lbeta[logical_value auto m](floating_value auto x, floating_value auto y)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [strictly positive real floating argument](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. the natural logarithm of the [beta](@ref beta) function.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/special/regular/lbeta.cpp}
//================================================================================================
 inline constexpr auto lbeta = functor<lbeta_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template< typename T, callable_options O>
    constexpr EVE_FORCEINLINE auto lbeta_(EVE_REQUIRES(cpu_), O const&, T a0, T a1)
    {
      return log_abs_gamma(a0) + log_abs_gamma(a1) - log_abs_gamma(a0 + a1);
    }
  }
}
