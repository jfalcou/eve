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
#include <eve/detail/hz_device.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/regular/log_abs_gamma.hpp>

namespace eve
{
template<typename Options>
struct trigamma_t : elementwise_callable<trigamma_t, Options>
{
  template<eve::floating_value T>
  constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(trigamma_t, trigamma_);
};

//================================================================================================
//! @addtogroup special
//! @{
//!   @var trigamma
//!   @brief `elementwise_callable` object computing the Trigamma function i.e.
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
//!      constexpr auto trigamma(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto trigamma[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto trigamma[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [floating_value](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of the Trigamma function: \f$\psi(x) = \frac{\Gamma'(x)}{\Gamma(x)}\f$ is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [DLMF: Gamma and Psi Functions](https://dlmf.nist.gov/5.2#i)
//!   *  [Wolfram MathWorld: Trigamma Function](https://mathworld.wolfram.com/TrigammaFunction.html)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/trigamma.cpp}
//================================================================================================
  inline constexpr auto trigamma = functor<trigamma_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr T  trigamma_(EVE_REQUIRES(cpu_), O const&, T z) noexcept
    {
      auto r = eve::nan(eve::as(z));
      auto done = eve::is_nan(z) || eve::is_minf(z);
      z = if_else(done, zero, z);
      auto ispinf = eve::is_pinf(z);
      done =  done || ispinf;
      r =if_else(ispinf, zero, r);
      z = if_else(ispinf, zero, z);


//       auto br_1_2 = [](auto x, auto result){ //is this better ?
//         // computes trigamma(a0)/a0 for double or double vectors
//         // xx is sqr(a0) and 0 <= abs(a0) <= 3.25
//         T y(0.99558162689208984);
//         T root1(1569415565.0 / 1073741824uL);
//         T root2((381566830.0 / 1073741824uL) / 1073741824uL);
//         T root3(0.9016312093258695918615325266959189453125e-19);

//         auto g = x - root1;
//         g -= root2;
//         g -= root3;
//         x = dec(x);
//         if constexpr( std::is_same_v<elt_t, double> )
//         {
//           auto r = eve::reverse_horner(x, T(0x1.04e9e69894978p-2), T(-0x1.4d5d0f9ab412fp-2), T(-0x1.4cf68d26e295ap-1)
//                                       , T(-0x1.2821c13c5e2bfp-2), T(-0x1.72b2e63723c78p-5), T(-0x1.0f7e5f66c2537p-9))/
//             eve::reverse_horner(x, T(0x1.0000000000000p+0), T(0x1.09d1b06674d41p+1), T(0x1.75eb79397c930p+0)
//                                , T(0x1.be65d28de361cp-2), T(0x1.bb9c8cc612ca3p-5), T(0x1.16fc90a0a1908p-9)
//                                , T(-0x1.2b84f95bbf448p-21));
//           return fma(g, y, g * r) + result;
//         }
//         else
//         {
//           auto r =
//           eve::reverse_horner(x, T(0x1.04e9e6p-2f), T(-0x1.4d5d10p-2f), T(-0x1.4cf68ep-1f), T(-0x1.2821c2p-2f)
//                              , T(-0x1.72b2e6p-5f), T(-0x1.0f7e60p-9f))/
//           eve::reverse_horner(x, T(0x1.000000p+0f), T(0x1.09d1b0p+1f), T(0x1.75eb7ap+0f), T(0x1.be65d2p-2f)
//                              , T(0x1.bb9c8cp-5f), T(0x1.16fc90p-9f), T(-0x1.2b84fap-21f));
//           return fma(g, y, g * r) + result;
//         }

      auto gez = eve::is_positive(z);

      auto br_neg = [gez](auto x){ //x <= 0
        x = if_else(gez, eve::mzero(as(x)), x);
        auto pi = eve::pi(eve::as(x));
        return eve::sqr(pi*eve::cscpi(x)) - trigamma(oneminus(x));
      };

      auto br_pos = [gez](auto x){//x >  0
        x = if_else(gez, x, eve::zero(eve::as(x)));
        auto psi = eve::zero(eve::as(x));
        constexpr int N = 10;
        auto test = x < N;
        if (eve::any(test))
        {
          auto n = N - eve::floor(x);
          psi += eve::if_else(test, eve::sqr(eve::rec(x)), zero);
          auto v = eve::one(eve::as(x));
          while(eve::any(test && v < n))
          {
            psi += if_else(test && v < n, eve::sqr(eve::rec(x+v)), zero);
            v = inc(v);
          }
          x = if_else(test, x+n, x);
        }
        auto t = eve::rec(x);
        auto w = eve::sqr(t);
        psi += t + eve::half(eve::as(x))*w;
        psi += t*w*eve::reverse_horner(w, 0.16666666666666666,-0.03333333333333333,0.023809523809523808,-0.03333333333333333
                              ,0.07575757575757576,-0.2531135531135531,1.1666666666666667,-7.092156862745098); //Bernouillis
        return psi;
      };

      auto notdone = !done;
      if (eve::any(notdone))
      {
        notdone = next_interval(br_pos, notdone, is_gtz(z), r, z);
        if( eve::any(notdone) )
        {
          last_interval(br_neg, notdone, r, z);
        }
      }
      return r;
    }
  }
}
