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
  struct pow1p_t : elementwise_callable<pow1p_t, Options, raw_option>
  {
    template<eve::floating_scalar_value T, eve::integral_scalar_value U>
    EVE_FORCEINLINE constexpr T operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    template<eve::floating_value T, eve::value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    EVE_FORCEINLINE constexpr common_value_t<T, U> operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    EVE_CALLABLE_OBJECT(pow1p_t, pow1p_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var pow1p
//!
//! @brief Callable object computing pow1p: \f$(1+x)^y\f$.
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
//!      constexpr auto pow1p(floating_value auto x, floating_value auto y)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto pow1p[conditional_expr auto c](floating_value auto x, floating_value auto y) noexcept; // 2
//!      constexpr auto pow1p[logical_value auto m](floating_value auto x, floating_value auto y)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto pow1p[raw](floating_value auto x, floating_value auto y)                     noexcept; // 3
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!     * `x`, `y`: [floating values](@ref floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!     1. Returns the [elementwise](@ref glossary_elementwise) \f$(1+x)^y\f$, with good accuracy,
//!        even when `x` is  small.
//!     2. [The operation is performed conditionnaly](@ref conditional)
//!     3. faster but less accurate call.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/regular/pow1p.cpp}
//!  @}
//================================================================================================
  inline constexpr auto pow1p = functor<pow1p_t>;

  namespace detail
  {

    template<floating_scalar_value T,  integral_scalar_value U, callable_options O>
    EVE_FORCEINLINE constexpr T
    pow1p_(EVE_REQUIRES(cpu_), O const & o, T a0, U a1) noexcept
    {
      return pow1p[o](a0, T(a1));
    }

    template<typename T,  typename U, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T, U>
    pow1p_(EVE_REQUIRES(cpu_), O const & o, T a, U b) noexcept
    {
      if constexpr(O::contains(raw2) || integral_value<U>)
         return pow[o](inc(a), b);
       else
       {
         using r_t =  common_value_t<T, U>;
         auto x =  r_t(a);
         auto y =  r_t(b);
         auto incx = inc(x);
         return if_else(abs(x) > half(as(x)), pow[o](incx, y), exp(y*log1p(x)));
       }
    }
  }
}
