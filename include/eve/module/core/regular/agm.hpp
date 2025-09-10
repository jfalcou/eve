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
#include <eve/module/core/constant/eps.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/any.hpp>
#include <eve/module/core/regular/mean_value.hpp>
#include <eve/module/core/regular/exponent.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/is_lez.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/ldexp.hpp>
#include <eve/module/core/regular/sign.hpp>
#include <eve/module/core/regular/sqrt.hpp>

namespace eve
{
  template<typename Options>
  struct agm_t : elementwise_callable<agm_t, Options>
  {
    template<eve::floating_value T,  floating_value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T a, U b) const
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(agm_t, agm_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var agm
//!   @brief `elementwise_callable` object computing the the arithmetic-geometric mean.
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
//!      // Regular overload
//!      constexpr auto agm(floating_value auto x, floating_value auto y)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto agm[conditional_expr auto c][floating_value auto x, floating_value auto y) noexcept; // 2.1
//!      constexpr auto agm[logical_value auto m](floating_value auto x, floating_value auto y)    noexcept; // 2.2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [floating values](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!    1. The value of the arithmetic-geometric mean is returned. No overflow can occur.
//!      The two parameters must share the same sign.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/Arithmetic-GeometricMean.html)
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Arithmetic-geometric_mean)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/agm.cpp}
//================================================================================================
  inline constexpr auto agm = functor<agm_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {

    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    agm_(EVE_REQUIRES(cpu_), O const &, T a,  T b) noexcept
    {
      auto ex = exponent(mean_value(a, b));
      auto r     = nan(as<T>());
      auto null = is_eqz(a)||is_eqz(b);
      r = if_else(null, zero, r);
      auto infi = is_infinite(a) || is_infinite(b);
      r = if_else(infi, a+b, r);
      auto unord = is_unordered(a, b);
      auto done = is_lez(sign(a)*sign(b)) || unord || infi;
      a = if_else(done,  zero, a);
      b = if_else(done,  zero, b);
      a =  ldexp(a, -ex);
      b =  ldexp(b, -ex);
      auto c  = mean_value(a, -b);
      while (eve::any(eve::abs(c) > T(2)*eps(as(c))))
      {
        auto an=mean_value(a, b);
        auto bn=sqrt(a*b);
        c=mean_value(a, -b);
        a=an;
        b=bn;
      }
      return if_else(done, r, ldexp(b, ex));
    }
  }
}
