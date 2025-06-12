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
#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/regular/zeta.hpp>
#include <eve/module/special/regular/trigamma.hpp>

namespace eve
{
template<typename Options>
struct hurwitz_t : elementwise_callable<hurwitz_t, Options>
{
  template<eve::value N, eve::floating_value T>
  constexpr EVE_FORCEINLINE T operator()(N n, T v) const  { return EVE_DISPATCH_CALL(n, v); }

  EVE_CALLABLE_OBJECT(hurwitz_t, hurwitz_);
};

//================================================================================================
//! @addtogroup special
//! @{
//!   @var hurwitz
//!   @brief `elementwise_callable` object computing the Hurwitz function i.e.
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
//!      constexpr auto hurwitz(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto hurwitz[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto hurwitz[logical_value auto m](floating_value auto x)    noexcept; // 2
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
//!     1. The value of the Hurwitz function: \f$\psi(x) = \frac{\Gamma'(x)}{\Gamma(x)}\f$ is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [DLMF: Gamma and Psi Functions](https://dlmf.nist.gov/5.2#i)
//!   *  [Wolfram MathWorld: Hurwitz Function](https://mathworld.wolfram.com/HurwitzFunction.html)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/hurwitz.cpp}
//================================================================================================
  inline constexpr auto hurwitz = functor<hurwitz_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<integral_value N, typename T, callable_options O>
    constexpr T  hurwitz_(EVE_REQUIRES(cpu_), O const&, N s, T x) noexcept
    {
      using r_t = eve::as_wide_as<T, N>;
      return hurwitz(eve::convert(s, eve::as(eve::element_type_t<r_t>())), x);
    }

    template<typename N, typename T, callable_options O>
    constexpr T  hurwitz_(EVE_REQUIRES(cpu_), O const&, N s, T z) noexcept
    {
      if constexpr(integral_value<N>)
      {
      using r_t = eve::as_wide_as<T, N>;
      return hurwitz(eve::convert(s, eve::as(eve::element_type_t<r_t>())), z);
      }
      else
      {
        using r_t = eve::common_value_t<N, T>;
        using elt_t =  eve::element_type_t<r_t>;
        if constexpr(scalar_value<r_t>)
        {
          if (z == 1 || z == 0) return eve::zeta(s);
          if (s == 2) return eve::trigamma(z);
          if (eve::is_nan(z) || eve::is_nan(s)) return z;
          if (eve::is_pinf(z)) return  eve::zero(eve::as(z));
          auto x = z;
          auto m = eve::dec(s);
          auto zeta =  eve::zero(eve::as(z));
          auto cutoff = 7 + m;
          if (x < cutoff) // shift using recurrence formula
          {
            //std::cout << "shift" << std::endl;
            auto xf = eve::floor(x);
            int  nx(xf);
            int n(eve::ceil(cutoff - nx));
            auto minus_s = -s;
            if (nx < 0)
            {
              auto minus_z = -z;
              zeta += eve::pow(minus_z, minus_s);
              if (xf != z)
              {
                zeta += pow(z - nx, minus_s);
              }
              if (s > 0)
              {
                for (int v = -nx-1; v >= 1;  --v){
                   auto zeta0 = zeta;
                   zeta+=eve::pow(minus_z - v, minus_s);
                   if(zeta == zeta0) break; // prevent long loop for large -x > 0
                }
              }
              else
              {
               for (int v = 1; v <= -nx-1; ++v){
                   auto zeta0 = zeta;
                   zeta+=eve::pow(minus_z - v, minus_s);
                   if(zeta == zeta0) break; // prevent long loop for large -x > 0
                }
              }
            }
            else // x ≥ 0 && z != 0
            {
              zeta += eve::pow(z, minus_s);
            }
            //# loop order depends on sign of s, as above
            if (s > 0)
            {
              for(int v=std::max(1, 1-nx); v <= n-1; ++v)
              {
                auto zeta0 = zeta;
                zeta+=eve::pow(z + v, minus_s);
                if(zeta == zeta0) break; // prevent long loop for large m
              }
            }
            else
            {
              for(int v=n-1; v >= std::max(1, 1-nx); --v)
              {
                auto zeta0 = zeta;
                zeta+=eve::pow(z + v, minus_s);
                if(zeta == zeta0) break; // prevent long loop for large m
              }
            }
            z += n;
          }
          auto t = eve::rec(z);
          auto w = pow(t, m);
          zeta += w * (eve::rec(m) + elt_t(0.5)*t);
          t *= t; // # 1/z^2;

          auto eval =  [](auto x, auto m){
            constexpr int M = 10;
            std::array<elt_t, M> p{0.0, 0.08333333333333333,-0.008333333333333333,0.003968253968253968,
                -0.004166666666666667,0.007575757575757576,-0.021092796092796094,
                0.08333333333333333,-0.4432598039215686,3.0539543302701198}; //B_2k/2k

            auto kk = M-1;
            auto ex = ((m + (2*kk-1))*(m+(2*kk-2))*(p[kk]/((2*kk-1)*(2*kk-2))));
            for(int k=M-2; k >= 2 ; k--)
            {
              auto cdiv = 1.0/((2*k-1)*(2*k-2));
              ex = ((cdiv*(m+(2*k-1))*(m + (2*k-2)))*((p[k]) + x * ex));
            }
            return ((m + 1) * ((p[1]) + x * ex));
          };
          zeta += w*t*eval(t, m);
          return zeta;
        }
        else
          return r_t{};
      }
    }
  }
}
