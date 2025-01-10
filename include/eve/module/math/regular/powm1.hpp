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
#include <eve/module/core.hpp>
#include <eve/module/math/regular/pow.hpp>

namespace eve
{
  template<typename Options>
  struct powm1_t : elementwise_callable<powm1_t, Options, raw_option>
  {
    template<eve::floating_scalar_value T, eve::integral_scalar_value U>
    EVE_FORCEINLINE constexpr T operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    template<eve::value T, eve::value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    EVE_FORCEINLINE constexpr common_value_t<T, U> operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    EVE_CALLABLE_OBJECT(powm1_t, powm1_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var powm1
//!
//! @brief Callable object computing powm1: \f$x^y-1\f$.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto powm1(floating_value auto x, floating_value auto y)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto powm1[conditional_expr auto c](floating_value auto x, floating_value auto y) noexcept; // 2
//!      constexpr auto powm1[logical_value auto m](floating_value auto x, floating_value auto y)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto powm1[raw](floating_value auto x, floating_value auto y)                     noexcept; // 3
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!    * `x`, `y`: [floating value](@ref eve::floating_value) arguments.
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) power minus one, with good accuracy,
//!       even when `y` is very small, or when `x` is close to 1.
//!    2. [The operation is performed conditionnaly](@ref conditional)
//!    3. faster but less accurate call.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/powm1.cpp}
//================================================================================================
  inline constexpr auto powm1 = functor<powm1_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {

    template<floating_scalar_value T, integral_scalar_value U, callable_options O>
    EVE_FORCEINLINE constexpr T
    powm1_(EVE_REQUIRES(cpu_), O const & o, T a0, U a1) noexcept
    {
      return powm1[o](a0, T(a1));
    }

    template<typename T,  typename U, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T, U>
    powm1_(EVE_REQUIRES(cpu_), O const & o, T a, U b) noexcept
    {
      using r_t =  common_value_t<T, U>;
      if constexpr(O::contains(raw))
      {
        return dec(pow[o](a, b));
      }
      else
      {
        auto x = r_t(a);
        auto y = r_t(b);
        auto r = dec(pow(x, y));
        auto test = (abs(y * dec(x)) < r_t(0.5) || (abs(y) < r_t(0.2)));
        if( eve::any(test) )
        {
          // We don't have any good/quick approximation for log(x) * y
          // so just try it and see:
          auto l = y*log_abs(x);
          auto tmp0 = expm1(l);
          auto tmp1 = minus[is_ltz(x) && is_odd(x)](tmp0);
          return if_else(l < T(0.5), tmp1, r);
        }
        else return r;
      }
    }
  }
}
