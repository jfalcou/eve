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
#include <iostream>

namespace eve
{
template<typename Options>
struct hurwitz2_t : callable<hurwitz2_t, Options>
{
  template<eve::value N, eve::floating_value T>
  constexpr EVE_FORCEINLINE T operator()(N n, T v) const  { return EVE_DISPATCH_CALL(n, v); }

  EVE_CALLABLE_OBJECT(hurwitz2_t, hurwitz2_);
};

//================================================================================================
//! @addtogroup special
//! @{
//!   @var hurwitz2
//!   @brief `elementwise_callable` object computing the Hurwitz2 function i.e.
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
//!      constexpr auto hurwitz2(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto hurwitz2[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto hurwitz2[logical_value auto m](floating_value auto x)    noexcept; // 2
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
//!     1. The value of the Hurwitz2 function: \f$\psi(x) = \frac{\Gamma'(x)}{\Gamma(x)}\f$ is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [DLMF: Gamma and Psi Functions](https://dlmf.nist.gov/5.2#i)
//!   *  [Wolfram MathWorld: Hurwitz2 Function](https://mathworld.wolfram.com/Hurwitz2Function.html)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/hurwitz2.cpp}
//================================================================================================
  inline constexpr auto hurwitz2 = functor<hurwitz2_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename N, typename T, callable_options O>
    constexpr T  hurwitz2_(EVE_REQUIRES(cpu_), O const&, N s, T z) noexcept
    {
      if constexpr(integral_value<N>)
      {
        return hurwitz2(T(s), z);
      }
      else
      {
        using r_t = eve::common_value_t<N, T>;
        using elt_t =  eve::element_type_t<r_t>;

        auto asymptotic =  [](auto x, auto m){
          constexpr int M = 10;
          std::array<elt_t, M> p{0.0, 0.08333333333333333,-0.008333333333333333,0.003968253968253968,
              -0.004166666666666667,0.007575757575757576,-0.021092796092796094,
              0.08333333333333333,-0.4432598039215686,3.0539543302701198}; //B_2k/2k

          auto kk = M-1;
          T ex((m + (2*kk-1))*(m+(2*kk-2))*(p[kk]/((2*kk-1)*(2*kk-2))));
          for(int k=M-2; k >= 2 ; k--)
          {
            auto cdiv = 1.0/((2*k-1)*(2*k-2));
            ex = ((cdiv*(m+(2*k-1))*(m + (2*k-2)))*((p[k]) + x * ex));
          }
          return ((m + 1) * ((p[1]) + x * ex));
        };

        auto scalar_1 = [s](auto zeta, auto xf, auto n, auto cutoff, auto z){
          std::cout << "scalar hurwitz2(" << s << ", " << z << ")" << std::endl;

          auto x = z;
          int  nx(xf);
          auto minus_s = -s;

          std::cout << "scalar --1 zeta " << zeta << std::endl;
          if (x < cutoff) // shift using recurrence formula
          {
            if (nx < 0)
            {
              std::cout << "scalar --2 zeta " << zeta << std::endl;
              auto minus_z = -z;
              zeta += eve::pow(minus_z, minus_s);
              if (xf != z)
              {
                zeta += pow(z - nx, minus_s);
              }
              std::cout << "simd --3 zeta " << zeta << std::endl;
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
              std::cout << "simd --3 zeta " << zeta << std::endl;
            }
            else // x ≥ 0 && z != 0
            {
              std::cout << "scalar --4 zeta " << zeta << std::endl;
              zeta += eve::pow(z, minus_s);
            }
          std::cout << "scalar --5 zeta " << zeta << std::endl;

          }
          std::cout << "hurwitz2 scalar --1 zeta" << zeta << std::endl;
          // loop order depends on sign of s, as above
          if (x < cutoff) // shift using recurrence formula
          {
            std::cout << "hurwitz2 2 scalar second loop" << std::endl;
            if (s > 0)
            {
               std::cout << "hurwitz2 2 scalar s > 0 " <<   s << std::endl;
             for(int v=std::max(1, 1-nx); v <= n-1; ++v)
              {
                auto zeta0 = zeta;
                zeta+=eve::pow(z + v, minus_s);
                if(zeta == zeta0) break; // prevent long loop for large m
              }
            }
            else
            {
              std::cout << "hurwitz2 2 scalar s <  0 " <<   s << std::endl;
              for(int v=n-1; v >= std::max(1, 1-nx); --v)
              {
                auto zeta0 = zeta;
                zeta+=eve::pow(z + v, minus_s);
                if(zeta == zeta0) break; // prevent long loop for large m
              }
            }
            std::cout << "hurwitz2 scalar --1 zeta" << zeta << std::endl;

            z += n;
            std::cout <<  "hurwitz2 2 z" << z << std::endl;
          }
          return zeta;

        };

        auto simd_1 = [s](auto zeta, auto xf, auto n, auto cutoff, auto z){
          std::cout << "simd hurwitz2(" << s << ", " << z << ")" << std::endl;

          auto x = z;
          auto  nx(xf);
          auto minus_s = -s;
          auto minus_z = -z;
          auto test1 = x < cutoff;
          auto test2 = nx < 0;
          auto test3 = test1 && test2;
          std::cout << "simd --1 zeta " << zeta << std::endl;
          if(eve::any(test1)) // shift using recurrence formula if  x < cutoff;
          {
            if (eve::any(test1 && test2))
            {
              zeta += if_else(test3, eve::pow(minus_z, minus_s), eve::zero);
              zeta += if_else(test3 && xf != z, pow(z - nx, minus_s), eve::zero);
            }
            std::cout << "simd --2 zeta " << zeta << std::endl;
            if (s > 0)
            {
              auto v = -nx-1;
              while ( eve::any(test3 && v >= 1))
              {
                auto zeta0 = zeta;
                zeta+=eve::if_else(test3 && v >= 1, eve::pow(minus_z - v, minus_s), zero);
                if(eve::all(zeta == zeta0)) break; // prevent long loop for large -x > 0
                v = eve::dec(v);
              }
//                  for (int v = -nx-1; v >= 1;  --v){
//                   auto zeta0 = zeta;
//                   zeta+=eve::pow(minus_z - v, minus_s);
//                   if(zeta == zeta0) break; // prevent long loop for large -x > 0
//                 }
            }
            else
            {
              auto v = eve::one(eve::as(nx));
              while (eve::any(test3 && v <= -nx-1))
              {
                auto zeta0 = zeta;
                zeta+= eve::if_else(test3 && v <= -nx-1,eve::pow(minus_z - v, minus_s), zero);
                if(eve::all(zeta == zeta0)) break; // prevent long loop for large -x > 0
                v = eve::inc(v);
              }
//                  for (int v = 1; v <= -nx-1; ++v){
//                  auto zeta0 = zeta;
//                   zeta+=eve::pow(minus_z - v, minus_s);
//                   if(zeta == zeta0) break; // prevent long loop for large -x > 0
//                 }
            }
            std::cout << "simd --3 zeta " << zeta << std::endl;
          }
          std::cout << "simd --4 zeta " << zeta << std::endl;
          if (eve::any(test1 && !test2)) // x ≥ 0 && z != 0
          {
            zeta += if_else(test1 && !test2, eve::pow(z, minus_s), zero);
          }
          std::cout << "simd --5 zeta " << zeta << std::endl;


//          std::cout << "hurwitz2 1 zeta" << zeta << std::endl;
          // loop order depends on sign of s, as above
          if(eve::any(test1)) // shift using recurrence formula
          {
            std::cout << "hurwitz2 2 simd second loop" << std::endl;
            if (s > 0)
            {
              std::cout << "hurwitz2 2 simd s > 0 " <<   s << std::endl;
              auto v = eve::max(eve::one(eve::as(n)), oneminus(nx));
              while (eve::any(test1 && eve::is_less_equal(v, dec(n))))
              {
                auto zeta0 = zeta;
                zeta+=eve::if_else(test1 && eve::is_less_equal(v, n-1), eve::pow(z + v, minus_s), zero);
                if(eve::all(zeta == zeta0)) break; // prevent long loop for large m
                v = inc(v);
              }
//               for(int v=std::max(1, 1-nx); v <= n-1; ++v)
//               {
//                 auto zeta0 = zeta;
//                 zeta+=eve::pow(z + v, minus_s);
//                 if(zeta == zeta0) break; // prevent long loop for large m
//               }
            }
            else
            {
              std::cout << "hurwitz2 2 simd s <= 0 " <<   s << std::endl;
              auto v = n-1;

              while (eve::any(test1 && eve::is_greater_equal(v, eve::max(eve::one(eve::as(nx)), oneminus(nx)))))
              {
                auto zeta0 = zeta;
                zeta+=eve::if_else(test1 && eve::is_greater_equal(v, eve::max(eve::one(eve::as(nx)), oneminus(nx))), eve::pow(z + v, minus_s), zero);
                if(eve::all(zeta == zeta0)) break; // prevent long loop for large m
                v = dec(v);
              }
//               for(int v=n-1; v >= std::max(1, 1-nx); --v)
//               {
//                 auto zeta0 = zeta;
//                 zeta+=eve::pow(z + v, minus_s);
//                 if(zeta == zeta0) break; // prevent long loop for large m
//               }
            }
            std::cout << "hurwitz2 2 simd --1 zeta" << zeta << std::endl;

            z += n;
            std::cout <<  "hurwitz2 2 z" << z << std::endl;
          }
          return zeta;

        };


        if (s == 2) return eve::trigamma(z);
        if (eve::is_nan(s)) return eve::nan(as(z));
        if (eve::all(z == eve::one(eve::as(z)) || eve::is_eqz(z))) return eve::zeta(r_t(s));
        if (eve::all(eve::is_nan(z))) return z;
        if (eve::all(eve::is_pinf(z))) return  eve::zero(eve::as(z));
        if (eve::all(eve::is_minf(z))) return  eve::nan(eve::as(z));

        elt_t m(dec(s));
        elt_t cutoff(7 + m);
        r_t zeta = eve::zero(eve::as<r_t>());
        auto xf = eve::floor(z);
        auto under_cutoff = z < cutoff;

        if constexpr(scalar_value<r_t>)
        {
          int nx(xf);
          int n(eve::ceil(cutoff - nx));
//          auto under_cutoff = z < cutoff;
          std::cout << "hurwitz2 scalar av scalar_1 zeta " << zeta <<  std::endl;
          zeta = scalar_1(zeta, xf, n, cutoff, z); //z+s+m+cutoff+asymptotic(z, m);
          z = if_else(under_cutoff, z+n, z);
          std::cout << "hurwitz2 av asymp z " << z <<  std::endl;
          auto t = eve::rec(z);
          auto w = pow(t, m);
          zeta += w * (eve::rec(m) + elt_t(0.5)*t);
          t *= t; // # 1/z^2;
          zeta += w*t*asymptotic(t, m);
          return zeta;
        }
        else // simd z
        {
          auto nx(xf);
          auto n(eve::ceil(cutoff - nx));
//          auto under_cutoff = z < cutoff;
          std::cout << "hurwitz2 simd av simd_1 zeta " << zeta <<  std::endl;
          zeta = simd_1(zeta, xf, n, cutoff, z);
          z = if_else(under_cutoff && z != eve::one(eve::as(z)) && eve::is_nez(z), z+n, z);
          std::cout << "hurwitz2 simd av asymp zeta " << zeta <<  std::endl;
          std::cout << "hurwitz2 simd av asymp z " << z <<  std::endl;
          std::cout << "hurwitz2 simd av asymp m " << m <<  std::endl;
          auto t = eve::rec(z);
          auto w = pow(t, m);
          zeta += w * (eve::rec(m) + elt_t(0.5)*t);
          t *= t; // # 1/z^2;
          zeta += w*t*asymptotic(t, m);
          zeta = eve::if_else(z == eve::one(eve::as(z)) || eve::is_eqz(z), eve::zeta(s), zeta);
          return zeta;
        }
      }
    }
  }
}
