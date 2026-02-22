//================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/zip.hpp>
#include <eve/module/core/regular/fms.hpp>
#include <iostream>

namespace eve
{
  template<typename Options>
  struct two_sqrt_approx_t : elementwise_callable<two_sqrt_approx_t, Options>
  {
    template<eve::floating_value T> constexpr EVE_FORCEINLINE
    zipped<T, T> operator()(T a) const
    {
      return EVE_DISPATCH_CALL(a);
    }

    EVE_CALLABLE_OBJECT(two_sqrt_approx_t, two_sqrt_approx_);
  };

//================================================================================================
//! @addtogroup core_accuracy
//! @{
//!   @var two_sqrt_approx
//!   @brief Computes the [elementwise](@ref glossary_elementwise)
//!   pair of square root and error,
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
//!      constexpr auto two_sqrt_approx(floating_value auto x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:  [floating arguments](@ref eve::floating_value).
//!
//!   **Return value**
//!
//!     Computes [elementwise](@ref glossary_elementwise) a pair of values `[a,e]` such that:
//!       * `a` is `eve::sqrt(x)`
//!       * `e` is a value such that `a`\f$\oplus\f$`e` is an approximation in doubled precision to `\f$\sqrt\f$`x`,
//!          where \f$\oplus\f$ (resp. \f$\sqrt\f$) adds (resp. take the square roots of) its parameters with
//!          infinite precision.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/two_sqrt_approx.cpp}
//================================================================================================
  inline constexpr auto two_sqrt_approx = functor<two_sqrt_approx_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE auto two_sqrt_approx_(EVE_REQUIRES(cpu_), O const&, T x)
    {
      auto r0 = eve::sqrt(x);
      auto e0 = if_else(is_not_finite(r0), zero, eve::fma[pedantic](-r0, r0, x)/(r0+r0));
      return eve::zip(r0,e0);
    }
  }
}
