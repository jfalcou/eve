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
struct polygamma_t : elementwise_callable<polygamma_t, Options>
{
  template<eve::value N, eve::floating_value T>
  constexpr EVE_FORCEINLINE T operator()(N n, T v) const  { return EVE_DISPATCH_CALL(n, v); }

  EVE_CALLABLE_OBJECT(polygamma_t, polygamma_);
};

//================================================================================================
//! @addtogroup special
//! @{
//!   @var polygamma
//!   @brief `elementwise_callable` object computing the Polygamma function i.e.
//!   the second derivative of the \f$\log\Gamma\f$  function.
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
//!      constexpr auto polygamma(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto polygamma[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto polygamma[logical_value auto m](floating_value auto x)    noexcept; // 2
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
//!     1. The value of the Polygamma function: \f$\psi(x) = \frac{\Gamma'(x)}{\Gamma(x)}\f$ is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [DLMF: Gamma and Psi Functions](https://dlmf.nist.gov/5.2#i)
//!   *  [Wolfram MathWorld: Polygamma Function](https://mathworld.wolfram.com/PolygammaFunction.html)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/polygamma.cpp}
//================================================================================================
  inline constexpr auto polygamma = functor<polygamma_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<integral_value N, typename T, callable_options O>
    constexpr T  polygamma_(EVE_REQUIRES(cpu_), O const&, N s, T x) noexcept
    {
      using r_t = eve::as_wide_as<T, N>;
      return polygamma(eve::convert(s, eve::as(eve::element_type_t<r_t>())), x);
    }

    template<typename N, typename T, callable_options O>
    constexpr T  polygamma_(EVE_REQUIRES(cpu_), O const&, N s, T x) noexcept
    {
      if constexpr(integral_value<N>)
      {
      using r_t = eve::as_wide_as<T, N>;
      return polygamma(eve::convert(s, eve::as(eve::element_type_t<r_t>())), x);
      }
      else
      {
        using r_t = eve::common_value_t<N, T>;
        using elt_t =  eve::element_type_t<r_t>;
        auto br_spec =  [](auto x){
          return zero(as(x));
        };

        auto br_else =  [](auto x, auto m){
//          auto t = eve::rec(x);
          elt_t  b = 10.0;
          auto value = eve::zero(as(x));
          int n = eve::maximum(if_else(x > b, eve::zero, eve::floor(b-x)));

          for(int i=n; i >= 0 ; --i)
          {
            value =  add[x+i != 0](value, pow(x+i, -m));
          }
          return value;
 //          x+= n+1;
//           auto w = pow(t, m);
//           auto y = w * eve::fam(eve::rec(m), eve::half(as(w)), t);

//           auto eval =  [](auto x, auto y, auto m)
//           {
//             constexpr int M = 9;
//             std::array<double, M> p{0.08333333333333333,-0.008333333333333333,0.003968253968253968,
//                                     -0.004166666666666667,0.007575757575757576,-0.021092796092796094,
//                                     0.08333333333333333,-0.4432598039215686,3.0539543302701198};
//             std::array<double, M> d;
//             d[0] = m+1;
//             for(int k=1; k < M ; ++k)
//             {
//               d[k] = (2*k+m-1)*(2*k+m-2) / ((2*k-1)*(2*k-2));
//             }
//             auto r = zero(as(y));
//             for(int i=M-1; i >= 0 ; --i)
//             {
//               r = r+d[i]*x*(p[i]+r);
//             }
//             return r;
//           };
//           auto z = eval(x, y, m);
//           auto t2 = eve::sqr(t);
//           y += w*t2 * z;
//           return value+y;
        };


        auto r       = nan(as<T>());                      // nan and zero case treated here
        r            = if_else(x == inf(as(x)), zero, r);
        auto notdone = eve::is_nez(x) && eve::is_not_nan(x) && (x != inf(as(x)));

        if( eve::any(notdone) )
        {
          notdone = next_interval(br_spec, notdone,eve::false_(eve::as(x)), r, x);
          if( eve::any(notdone) )
          {
            notdone = last_interval(br_else, notdone, r, x, s-1);
          }
        }
        return r;
      }
    }
  }
}
