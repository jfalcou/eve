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
struct hurwitz_t : callable<hurwitz_t, Options>
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
    template<typename N, typename T, callable_options O>
    constexpr T  hurwitz_(EVE_REQUIRES(cpu_), O const&, N s, T z) noexcept
    {
      if constexpr(integral_value<N>)
      {
        return hurwitz(T(s), z);
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

        if (s == 2) return eve::trigamma(z);
        if (eve::is_nan(s)) return eve::nan(as(z));
        if (eve::all(z == eve::one(eve::as(z)) || eve::is_eqz(z))) return eve::zeta(r_t(s));
        if (eve::all(eve::is_nan(z))) return z;
        if (eve::all(eve::is_pinf(z))) return  eve::zero(eve::as(z));
        if (eve::all(eve::is_minf(z))) return  eve::nan(eve::as(z));

        elt_t m(dec(s));
        elt_t cutoff(7 + m);

        if constexpr(scalar_value<r_t>)
        {
          std::cout << "scalar hurwitz(" << s << ", " << z << ")" << std::endl;

          auto x = z;

          auto zeta =  eve::zero(eve::as(z));
          std::cout << "cutoff " << cutoff << std::endl;
          if (x < cutoff) // shift using recurrence formula
          {
            std::cout << "shift" << std::endl;
            auto xf = eve::floor(x);
            int  nx(xf);
            int n(eve::ceil(cutoff - nx));
            //std::cout << "1-- m " <<  m << " z " << z << " nx " <<  nx << " n " << n << std::endl;
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
                //std::cout <<  "2-- s > 0, m " <<  m << " z " << z << " nx " <<  nx << " n " << n << std::endl;
                for (int v = -nx-1; v >= 1;  --v){
                   auto zeta0 = zeta;
                   zeta+=eve::pow(minus_z - v, minus_s);
                   if(zeta == zeta0) break; // prevent long loop for large -x > 0
                }
              }
              else
              {
                //std::cout <<  "3-- s <  0, m " <<  m << " z " << z << " nx " <<  nx << " n " << n << std::endl;
                for (int v = 1; v <= -nx-1; ++v){
                   auto zeta0 = zeta;
                   zeta+=eve::pow(minus_z - v, minus_s);
                   if(zeta == zeta0) break; // prevent long loop for large -x > 0
                }
              }
              std::cout << "nnx " << nx <<  std::endl;
              std::cout << "z   " << z   <<  std::endl;
              std::cout << " 1 zeta " << zeta<<  std::endl;
              std::cout << "no supplementary term" << std::endl;
             }
            else // x ≥ 0 && z != 0
            {
              zeta += eve::pow(z, minus_s);
              std::cout << "nnx " << nx <<  std::endl;
              std::cout << "z   " << z   <<  std::endl;
              std::cout << " 2 zeta " << zeta<<  std::endl;
              std::cout << "supplementary term" << std::endl;
           }

            // loop order depends on sign of s, as above
            if (s > 0)
            {
              std::cout << "icitte " << zeta << std::endl;
              //std::cout <<  "4-- s > 0, m " <<  m << " z " << z << " nx " <<  nx << " n " << n << std::endl;
              for(int v=std::max(1, 1-nx); v <= n-1; ++v)
              {
                auto zeta0 = zeta;
                zeta+=eve::pow(z + v, minus_s);
                if(zeta == zeta0) break; // prevent long loop for large m
              }
              std::cout <<  "icitte zeta " << zeta << std::endl;
           }
            else
            {
              //std::cout <<  "5-- s < 0, m " <<  m << " z " << z << " nx " <<  nx << " n " << n << std::endl;
               for(int v=n-1; v >= std::max(1, 1-nx); --v)
              {
                auto zeta0 = zeta;
                zeta+=eve::pow(z + v, minus_s);
                if(zeta == zeta0) break; // prevent long loop for large m
              }
            }
            z += n;
              std::cout << "av asympt "<<  std::endl;
              std::cout << "z    " << z   <<  std::endl;
              std::cout << " 3 zeta " << zeta<<  std::endl;

          }
          //std::cout << "av scalar asympt " << z << " -> r " << zeta << std::endl;
          auto t = eve::rec(z);
          auto w = pow(t, m);
          //std::cout << "t " << t << " w " << w << std::endl;
          //std::cout << "rm " << eve::rec(m) <<  std::endl;
          //std::cout << "(eve::rec(m) + elt_t(0.5)*t) " << (eve::rec(m) + elt_t(0.5)*t) << std::endl;
          zeta += w * (eve::rec(m) + elt_t(0.5)*t);
          t *= t; // # 1/z^2;
          //std::cout << "asymptotic(t, m) " << asymptotic(t, m) <<  std::endl;
          zeta += w*t*asymptotic(t, m);
          //std::cout << "r " << zeta <<std::endl;
          return zeta;
        }
        else // simd z
        {
          std::cout << "hurwitz(" << s << ", " << z << ")" << std::endl;

          auto r = nan(as(z));
          r = eve::if_else(eve::is_pinf(z), r, eve::zero);
          auto notdone = is_not_nan(z)|| is_not_infinite(z);

          std::cout << "cutoff " << cutoff << std::endl;

          auto n = eve::ceil(cutoff - eve::floor(z));

          auto br_pinf = [](){  //eve::is_pinf(z)
            return eve::zero(as<r_t>());
          };


          auto br_shift = [cutoff, s, &z, n](auto x){  // x <= cutoff
            std::cout << "shift" << std::endl;
            auto zeta =  eve::zero(eve::as(x));
            x = if_else(x > cutoff, cutoff, x);
            auto xf = eve::floor(x);
            auto  nnx(xf);
            //  auto n = eve::ceil(cutoff - nnx);
            //std::cout << "1-- m " <<  m << " z " << z << " nnx " <<  nnx << std::endl;
            auto minus_s = -s;

            auto br_nx_neg = [xf, nnx, s, minus_s](auto z){ //nx < 0
                 auto nx = nnx;
              // auto nx = eve::if_else(eve::is_gez(nnx), eve::mone, nnx);
              auto minus_z = -z;
              auto zeta = eve::pow(minus_z, minus_s);
              zeta += if_else(xf != z, pow(z - nx, minus_s),  zero);
              if(s > 0)
              {
                //std::cout <<  "2-- s > 0, m " <<  m << " z " << z << " nx " <<  nx << std::endl;
                auto v = -nx-1;
                while (eve::any(v >= 1))
                {
                  auto zeta0 = zeta;
                  zeta+=eve::if_else(v >= 1, eve::pow(minus_z - v, minus_s), zero);
                  if(eve::all(zeta == zeta0)) break; // prevent long loop for large -x > 0
                  v = eve::dec(v);
                }
              }
              else
              {
                //std::cout <<  "3-- s <  0, m " <<  m << " z " << z << " nx " <<  nx << std::endl;
                auto v = eve::one(eve::as(nx));
                while (eve::any(v <= -nx-1))
                {
                  //     for (int v = 1; v <= -nx-1; ++v){
                  auto zeta0 = zeta;
                  zeta+= eve::if_else(v <= -nx-1,eve::pow(minus_z - v, minus_s), zero);
                  if(eve::all(zeta == zeta0)) break; // prevent long loop for large -x > 0
                  v = eve::inc(v);
                }
              }
              std::cout << "nnx " << nx <<  std::endl;
              std::cout << "z   " << z   <<  std::endl;
              std::cout << " 4 zeta " << zeta<<  std::endl;
              return zeta;
            };

            std::cout << " -- nnx " << nnx <<  std::endl;
            std::cout << " -- z   " << z   <<  std::endl;
            zeta = if_else(eve::is_ltz(nnx), br_nx_neg(z), eve::zero);// if_else(is_gtz(z), br_nx_pos(z), eve::zero));
            std::cout << " -- zeta   " << zeta   <<  std::endl;
            auto nx = nnx;
            if (s > 0)
            {
              std::cout << "icitte " << zeta << std::endl;
              //std::cout <<  "4-- s > 0, m " <<  m << " z " << z << " n " << n << std::endl;
              auto v = eve::max(eve::one(eve::as(n)), oneminus(nx));
//              for(int v=std::max(1, 1-nx); v <= n-1; ++v)
              while (eve::any(eve::is_less_equal(v, dec(n))))
              {
                auto zeta0 = zeta;
                zeta+=eve::if_else(eve::is_less_equal(v, n-1), eve::pow(z + v, minus_s), zero);
                if(eve::all(zeta == zeta0)) break; // prevent long loop for large m
                v = inc(v);
              }
              std::cout <<  "icitte zeta " << zeta << std::endl;
            }
            else
            {
              //std::cout <<  "5-- s < 0, m " <<  m << " z " << z << " n " << n << std::endl;
              auto v = n-1; //eve::max(eve::one(eve::as(nx)), oneminus(nx));
//               for(int v=n-1; v >= std::max(1, 1-nx); --v)
              while (eve::any(eve::is_greater_equal(v, eve::max(eve::one(eve::as(nx)), oneminus(nx)))))
              {
                auto zeta0 = zeta;
                zeta+=eve::if_else(eve::is_greater_equal(v, eve::max(eve::one(eve::as(nx)), oneminus(nx))), eve::pow(z + v, minus_s), zero);
                if(eve::all(zeta == zeta0)) break; // prevent long loop for large m
                v = dec(v);
              }
            }
            z = z+n;
            std::cout << "av asympt "<<  std::endl;
            std::cout << "z    " << z   <<  std::endl;
            std::cout << " 5 zeta " << zeta<<  std::endl;

            if (eve::any(z < cutoff && nnx < 0)) std::cout <<  "supplementary term" << std::endl;  else  std::cout <<  "no supplementary term" << std::endl;
            zeta +=  if_else(z < cutoff, eve::pow(z, minus_s), eve::zero);
            return zeta;
          };


          if( eve::any(notdone) )
          {
            notdone = next_interval(br_pinf, notdone, is_pinf(z), r);
            if( eve::any(notdone) )
            {
              notdone      = last_interval(br_shift, notdone, r, z);
            }
          }
//          z += if_else(z < cutoff, n, zero);
          //std::cout << "av simd asympt " << z << " r " << r << std::endl;
          auto t = eve::rec(z);
          auto w = pow(t, m);
          //std::cout << "t " << t << " w " << w << std::endl;
          //std::cout << "rm " << eve::rec(elt_t(m)) <<  std::endl;
          //std::cout << "(eve::rec(elt_t(m)) + elt_t(0.5)*t) " << (eve::rec(m) + elt_t(0.5)*t) << std::endl;
          r += w * (eve::rec(elt_t(m)) + elt_t(0.5)*t);
          t *= t; // # 1/z^2;

          r += w*t*asymptotic(t, m);
          //std::cout << "r " << r <<std::endl;
          return r;
        }
      }
    }
  }
}
