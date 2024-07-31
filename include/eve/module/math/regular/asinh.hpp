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
#include <eve/module/math/constant/log_2.hpp>
#include <eve/module/math/hypot.hpp>
#include <eve/module/math/log.hpp>
#include <eve/module/math/log1p.hpp>
#include <eve/module/math/reverse_horner.hpp>

namespace eve
{
  template<typename Options>
  struct asinh_t : elementwise_callable<asinh_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(asinh_t, asinh_);
};


//================================================================================================
//! @addtogroup math_invhyper
//! @{
//!   @var asinh
//!   @brief `elementwise_callable` object computing the inverse hyperbolic
//!   sine :\f$\log(x+\sqrt{x^2+1})\f$.
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
//!      constexpr auto asinh(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto asinh[conditional_expr auto c](floating_value auto x) noexcept; // 2.1
//!      constexpr auto asinh[logical_value auto m](floating_value auto x)    noexcept; // 2.2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [floating value](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic sine of the
//!      input in the range  \f$[-\frac\pi2, \frac\pi2]\f$.
//!      In particular:
//!      * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, \f$\pm\infty\f$ returned.
//!      * If the element is a `NaN`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/asinh)
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/InverseHyperbolicSine.html)
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Inverse_hyperbolic_functions)
//!   *  [DLMF](https://dlmf.nist.gov/4.37)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/asinh.cpp}
//!  @}
//======================================================================================================================
  inline constexpr auto asinh = functor<asinh_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T asinh_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      using vt_t = element_type_t<T>;
      T x        = eve::abs(a0);
      if constexpr( scalar_value<T> )
        if( x < sqrteps(eve::as<T>()) ) return a0; // scalar early return
      auto x_gt_oneosqrteps = x > oneosqrteps(eve::as<T>());
      auto bts              = bitofsign(a0);
      if constexpr( std::is_same_v<vt_t, double> )
      {
        if constexpr( scalar_value<T> ) // faster for great or small values
        {
          if( x_gt_oneosqrteps ) return bit_xor(log(x) + log_2(eve::as<T>()), bts);
          else if( x >= eve::half(eve::as<T>()) )
            return bit_xor(log(x + hypot(one(eve::as<T>()), x)), bts);
        }
        // remaining scalar case and all simd cases to avoid multiple computations as
        // this one is always ok
        T z = if_else(x_gt_oneosqrteps, dec(x), x + sqr(x) / eve::inc(hypot(one(eve::as<T>()), x)));
        if constexpr( eve::platform::supports_infinites ) z = if_else((x == inf(eve::as<T>())), x, z);
        z = add[x_gt_oneosqrteps](eve::log1p(z), log_2(eve::as<T>()));
        return bit_xor(z, bts);
      }
      else if constexpr( std::is_same_v<vt_t, float> )
      {
        auto        x_lt_half = x < half(eve::as<T>());
        T           x2        = sqr(x);
        T           z         = zero(eve::as<T>());
        std::size_t nb        = eve::count_true(x_lt_half);
        if( nb > 0 )
        {
          z = eve::reverse_horner(x2, T(0x1.000000p+0f), T(-0x1.55535ap-3f), T(0x1.329362p-4f)
                                 , T(-0x1.5dcb02p-5f), T(0x1.49adccp-6f))* x;
          if( nb >= cardinal_v<T> ) return bit_xor(z, bts);
        }
        auto case_1 = [](T const& x) { return x; };                                       // great x
        auto case_2 = [](T const& x) { return average(x, hypot(one(eve::as<T>()), x)); }; // lesser x
        auto tmp    = branch<scalar_value<T>>(x_gt_oneosqrteps, case_1, case_2)(x);
        auto z1     = bit_xor(if_else(x_lt_half, z, log(tmp) + log_2(eve::as<T>())), bts);
        if constexpr( eve::platform::supports_invalids )
          return if_else(is_nan(a0), eve::allbits, z1);
        else
          return z1;
      }
    }
  }
}
