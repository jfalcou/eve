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

namespace eve
{
template<typename Options>
struct hurwitz_t : callable<hurwitz_t, Options>
{
  template<eve::scalar_value N, eve::floating_value T>
  constexpr EVE_FORCEINLINE T operator()(N n, T v) const  { return EVE_DISPATCH_CALL(n, v); }

  EVE_CALLABLE_OBJECT(hurwitz_t, hurwitz_);
};

//================================================================================================
//! @addtogroup special
//! @{
//!   @var hurwitz
//!   @brief `elementwise_callable` object computing the Hurwitz function i.e.
//!   \f$\sum_{k=0}^\infty (k+z)^{-s}\f$, where any term with \f$k+z = 0\f$ is excluded.
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
//!     1. The value of the Hurwitz function:  \f$\sum_{k=0}^\infty (k+z)^{-s}\f$, where any term with \f$k+z = 0\f$ is excluded.
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
    template<typename N, typename T, callable_options O>
    constexpr T  hurwitz_(EVE_REQUIRES(cpu_), O const&, N s, T z) noexcept
    {
      using r_t = T;
      using elt_t =  eve::element_type_t<r_t>;
      if constexpr(integral_value<N>)
      {
        return hurwitz(elt_t(s), z);
      }
      else
      {

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

        auto scalar_1 = [s](auto zeta, auto xf, auto n, auto cutoff, auto zz){
          auto x = zz;
          int  nx(xf);
          auto minus_s = -s;

          if (x < cutoff) // shift using recurrence formula
          {
            if (nx < 0)
            {
              auto minus_z = -zz;
              zeta += eve::pow(minus_z, minus_s);
              if (xf != zz)
              {
                zeta += pow(zz - nx, minus_s);
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
            else // x $(C!C(B 0 && z != 0
            {
              zeta += eve::pow(zz, minus_s);
            }
          }
          // loop order depends on sign of s, as above
          if (x < cutoff) // shift using recurrence formula
          {
            if (s > 0)
            {
             for(int v=std::max(1, 1-nx); v <= n-1; ++v)
              {
                auto zeta0 = zeta;
                zeta+=eve::pow(zz + v, minus_s);
                if(zeta == zeta0) break; // prevent long loop for large m
              }
            }
            else
            {
              for(int v=n-1; v >= std::max(1, 1-nx); --v)
              {
                auto zeta0 = zeta;
                zeta+=eve::pow(zz + v, minus_s);
                if(zeta == zeta0) break; // prevent long loop for large m
              }
            }
            zz += n;
          }
          return zeta;

        };

        auto simd_1 = [s](auto zeta, auto xf, auto n, auto cutoff, auto zz){
          auto x = zz;
          auto  nx(xf);
          auto minus_s = -s;
          auto minus_z = -zz;
          auto test1 = x < cutoff;
          auto test2 = nx < 0;
          auto test3 = test1 && test2;
          if(eve::any(test1)) // shift using recurrence formula if  x < cutoff;
          {
            if (eve::any(test1 && test2))
            {
              zeta += if_else(test3, eve::pow(minus_z, minus_s), eve::zero);
              zeta += if_else(test3 && xf != zz, pow(zz - nx, minus_s), eve::zero);
            }
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
            }
          }
          if (eve::any(test1 && !test2)) // x $(C!C(B 0 && z != 0
          {
            zeta += if_else(test1 && !test2, eve::pow(zz, minus_s), zero);
          }
          // loop order depends on sign of s, as above
          if(eve::any(test1)) // shift using recurrence formula
          {
            if (s > 0)
            {
              auto v = eve::max(eve::one(eve::as(n)), oneminus(nx));
              while (eve::any(test1 && eve::is_less_equal(v, dec(n))))
              {
                auto zeta0 = zeta;
                zeta+=eve::if_else(test1 && eve::is_less_equal(v, n-1), eve::pow(zz + v, minus_s), zero);
                if(eve::all(zeta == zeta0)) break; // prevent long loop for large m
                v = inc(v);
              }
            }
            else
            {
              auto v = n-1;

              while (eve::any(test1 && eve::is_greater_equal(v, eve::max(eve::one(eve::as(nx)), oneminus(nx)))))
              {
                auto zeta0 = zeta;
                zeta+=eve::if_else(test1 && eve::is_greater_equal(v, eve::max(eve::one(eve::as(nx)), oneminus(nx))), eve::pow(zz + v, minus_s), zero);
                if(eve::all(zeta == zeta0)) break; // prevent long loop for large m
                v = dec(v);
              }
            }
            zz += n;
          }
          return zeta;
        };

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
          zeta = scalar_1(zeta, xf, n, cutoff, z);
          z = if_else(under_cutoff, z+n, z);
          auto t = eve::rec(z);
          auto w = pow(t, m);
          zeta += w * (eve::rec(m) + elt_t(0.5)*t);
          t *= t; //  1/z^2;
          zeta += w*t*asymptotic(t, m);
          return zeta;
        }
        else // simd z
        {
          auto zeta0 = eve::nan(eve::as(z));
          auto done = eve::is_nan(z) || eve::is_minf(z);
          z = if_else(done, zero, z);
          auto ispinf = eve::is_pinf(z);
          done =  done || ispinf;
          zeta0 =if_else(ispinf, zero, zeta0);
          z = if_else(ispinf, zero, z);

          auto nx(xf);
          auto n(eve::ceil(cutoff - nx));
          zeta = simd_1(zeta, xf, n, cutoff, z);
          z = if_else(under_cutoff && z != eve::one(eve::as(z)) && eve::is_nez(z), z+n, z);
          auto t = eve::rec(z);
          auto w = pow(t, m);
          zeta += w * (eve::rec(m) + elt_t(0.5)*t);
          t *= t; // # 1/z^2;
          zeta += w*t*asymptotic(t, m);
          zeta = eve::if_else(z == eve::one(eve::as(z)) || eve::is_eqz(z), eve::zeta(s), zeta);
          return if_else(done, zeta0, zeta);
        }
      }
    }
  }
}
