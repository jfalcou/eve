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
#include <eve/module/math/regular/expm1.hpp>

namespace eve
{
  template<typename Options>
  struct tanh_t : elementwise_callable<tanh_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(tanh_t, tanh_);
  };

//================================================================================================
//! @addtogroup math_hyper
//! @{
//! @var tanh
//!
//! @brief `elementwise_callable` object computing \f$\frac{e^x-e^{-x}}{e^x+e^{-x}}\f$.
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
//!      constexpr auto tanh(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto tanh[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto tanh[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!     * `x`: [floating value](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!   1. Returns the [elementwise](@ref glossary_elementwise) hyperbolic tangent of the input.
//!      In particular:
//!        * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!        * If the element is \f$\pm\infty\f$, \f$\pm1\f$ returned.
//!        * If the element is a `NaN`, `NaN` is returned.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/tanh)
//!   *  [Wikipedia](https://fr.wikipedia.org/wiki/Hyperbolic_functions)
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/HyperbolicTangent.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/tanh.cpp}
//================================================================================================
  inline constexpr auto tanh = functor<tanh_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T tanh_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(a0) ) return a0;
      }
      auto x    = eve::abs(a0 + a0);
      auto test = x > T(0.5493) * 2;
      auto t    = expm1(x);
      auto rt2  = rec[pedantic](t + T(2));
      if constexpr( scalar_value<T> )
      {
        auto r = test ? fnma(T(2), rt2, T(1)) : t * rt2;
        return copysign(r, a0);
      }
      else if constexpr( simd_value<T> )
      {
        auto z1 = fnma(T(2), rt2, T(1));
        auto z2 = t * rt2;
        auto r  = if_else(test, z1, z2);
        return copysign(r, a0);
      }
    }
  }
}
