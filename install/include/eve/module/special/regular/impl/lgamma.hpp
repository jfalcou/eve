//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{
////////////////////////////////////////////////////////////////////////////////////////////////////
/// helpers
template<floating_real_value T>
inline T
large_negative(T q)
{
  T    w     = eve::lgamma(q);
  T    p     = floor(q);
  T    z     = q - p;
  auto test2 = (z < half(as<T>()));
  z          = dec[test2](z);
  z          = q * sinpi(z);
  z          = abs(z);
  return T(1.1447298858494001741434273513530587116472948129153) - log(z) - w;
}

template<floating_real_value T>
EVE_FORCEINLINE T
lgammaB(T x) noexcept
{
  // log gamma(x+2), -.5 < x < .5
  return horn<T,
              0x3ed87730U, //    4.227843421859038E-001
              0x3ea51a64U, //    3.224669577325661E-001,
              0xbd89f07eU, //   -6.735323259371034E-002,
              0x3ca89ed8U, //    2.058355474821512E-002,
              0xbbf164fdU, //   -7.366775108654962E-003,
              0x3b3ba883U, //    2.863437556468661E-003,
              0xbaabeab1U, //   -1.311620815545743E-003,
              0x3a1ebb94U  //    6.055172732649237E-004
              >(x);
}
template<floating_real_value T>
EVE_FORCEINLINE T
lgammaC(T x) noexcept
{
  // log gamma(x+1), -.25 < x < .25
  return horn<T,
              0xbf13c468U, //   -5.772156501719101E-001
              0x3f528d34U, //    8.224670749082976E-001,
              0xbecd27a8U, //   -4.006931650563372E-001,
              0x3e8a898bU, //    2.705806208275915E-001,
              0xbe53c04fU, //   -2.067882815621965E-001,
              0x3e2d4dabU, //    1.692415923504637E-001,
              0xbe22d329U, //   -1.590086327657347E-001,
              0x3e0c3c4fU  //    1.369488127325832E-001
              >(x);
}
template<floating_real_value T>
EVE_FORCEINLINE T
lgamma2(T p) noexcept
{
  return horn<T,
              0x3daaaa94U, //   8.333316229807355E-002f
              0xbb358701U, //  -2.769887652139868E-003f,
              0x3a31fd69U  //   6.789774945028216E-004f
              >(p);
}

template<floating_real_value T>
EVE_FORCEINLINE T
lgamma1(T x) noexcept
{
  return horn<T,
              0xc12a0c675418055eULL, //  -8.53555664245765465627E5
              0xc13a45890219f20bULL, //  -1.72173700820839662146E6,
              0xc131bc82f994db51ULL, //  -1.16237097492762307383E6,
              0xc1143d73f89089e5ULL, //  -3.31612992738871184744E5,
              0xc0e2f234355bb93eULL, //  -3.88016315134637840924E4,
              0xc09589018ff36761ULL  //  -1.37825152569120859100E3
              >(x)
         / horn<T,
                0xc13ece4b6a11e14aULL, //  -2.01889141433532773231E6
                0xc1435255892ff34cULL, //  -2.53252307177582951285E6,
                0xc131628671950043ULL, //  -1.13933444367982507207E6,
                0xc10aeb84b9744c9bULL, //  -2.20528590553854454839E5,
                0xc0d0aa0d7b89d757ULL, //  -1.70642106651881159223E4,
                0xc075fd0d1cf312b2ULL, //  -3.51815701436523470549E2,
                0x3ff0000000000000ULL  //   1.00000000000000000000E0
                >(x);
}

template<floating_real_value T>
EVE_FORCEINLINE T
lgammaA(const T& p) noexcept
{
  return horn<T,
              0x3fb555555555554bULL, //    8.33333333333331927722E-2
              0xbf66c16c16b0a5a1ULL, //   -2.77777777730099687205E-3,
              0x3f4a019f20dc5ebbULL, //    7.93650340457716943945E-4,
              0xbf437fbdb580e943ULL, //   -5.95061904284301438324E-4,
              0x3f4a985027336661ULL  //    8.11614167470508450300E-4
              >(p);
}

template<floating_real_value T>
constexpr T
lgamma_(EVE_SUPPORTS(cpu_), T a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    const T Logsqrt2pi = T(0.91893853320467274178032973640561763986139747363777);
    using elt_t        = element_type_t<T>;
    if constexpr( std::is_same_v<elt_t, float> )
    {
      if constexpr( scalar_value<T> ) // float scalar
      {
        if( (is_infinite(a0)) ) return inf(as<T>());
        const T Maxlgamma =
            Ieee_constant<T, 0x7bc3f8eaU, 0x7f574c5dd06d2516ULL>(); // 2.035093e36f, 2.556348e305
        auto lgamma_pos = [Logsqrt2pi](T x)
        {
          if( x < 6.5f )
          {
            T z  = one(as<T>());
            T tx = x;
            T nx = zero(as<T>());
            if( x >= 1.5f )
            {
              while( tx > 2.5f )
              {
                nx = dec(nx);
                tx = x + nx;
                z *= tx;
              }
              x += nx - T(2);
              T p = x * lgammaB(x);
              return p + log(z);
            }
            if( x >= 1.25f )
            {
              z *= x;
              x   = dec(x);
              T p = x * lgammaB(x);
              return p - log(z);
            }
            if( x >= 0.75f )
            {
              x = dec(x); //-= 1.0f;
              return x * lgammaC(x);
            }
            while( tx < 1.5f )
            {
              if( is_eqz(tx) ) return inf(as<T>());
              z *= tx;
              nx = inc(nx);
              tx = x + nx;
            }
            x += nx - T(2);
            T p = x * lgammaB(x);
            return p - log(z);
          }
          T q = fma((x - 0.5f), log(x), Logsqrt2pi - x);
          if( x <= 1.0e4f )
          {
            T z = rec(x);
            T p = sqr(z);
            q   = fma(z, lgamma2(p), q);
          }
          return q;
        };

        if( (a0 > Maxlgamma) || is_eqz(a0) ) return inf(as<T>());
        T x = a0;
        T q = abs(x);
        if( x < 0.0f )
        {
          if( q > Maxlgamma ) return nan(as<T>());
          T w = lgamma_pos(q);
          T p = floor(q);
          if( p == q ) return inf(as<T>());
          T z = q - p;
          if( z > half(as<T>()) )
          {
            p += one(as<T>());
            z = p - q;
          }
          z = q * sinpi(z);
          if( is_eqz(z) ) return inf(as<T>());
          return -log(inv_pi(as<T>()) * abs(z)) - w;
        }
        else { return lgamma_pos(x); }
      }
      else if constexpr( simd_value<T> ) // float simd
      {
        auto inf_result = (is_lez(a0) && is_flint(a0)) || is_infinite(a0);
        T    x          = if_else(inf_result, eve::allbits, a0);
        T    q          = abs(x);
        if constexpr( eve::platform::supports_infinites )
        {
          inf_result = (x == inf(as<T>())) || inf_result;
        }
        auto   ltza0 = is_ltz(a0);
        size_t nb    = eve::count_true(ltza0);
        T      r {0};
        auto   other = [Logsqrt2pi](T x)
        {
          auto   xlt650 = is_less(x, T(6.50));
          size_t nb     = eve::count_true(xlt650);
          T      r0x    = x;
          T      r0z    = x;
          T      r0s    = one(as<T>());
          T      r1     = zero(as<T>());
          T      p      = nan(as<T>());
          if( nb > 0 )
          {
            auto kernelC = false_(as<T>());
            T    z       = one(as<T>());
            T    tx      = if_else(xlt650, x, eve::zero);
            T    nx      = zero(as<T>());

            const T _075    = T(0.75);
            const T _150    = T(1.50);
            const T _125    = T(1.25);
            const T _250    = T(2.50);
            auto    xge150  = (x >= _150);
            auto    txgt250 = (tx > _250);

            // x >= 1.5
            while( eve::any(logical_and(xge150, txgt250)) )
            {
              nx      = dec[txgt250](nx);
              tx      = if_else(txgt250, x + nx, tx);
              z       = if_else(txgt250, z * tx, z);
              txgt250 = (tx > _250);
            }
            r0x = add[xge150](x, nx - T(2));
            r0z = if_else(xge150, z, r0z);
            r0s = if_else(xge150, one(as<T>()), r0s);

            // x >= 1.25 && x < 1.5
            auto xge125  = (x >= _125);
            auto xge125t = logical_andnot(xge125, xge150);
            if( eve::any(xge125) )
            {
              r0x = if_else(xge125t, dec(x), r0x);
              r0z = if_else(xge125t, z * x, r0z);
              r0s = if_else(xge125t, mone(as<T>()), r0s);
            }
            // x >= 0.75&& x < 1.5
            auto xge075  = (x >= _075);
            auto xge075t = logical_andnot(xge075, xge125);
            if( eve::any(xge075t) )
            {
              kernelC = xge075t;
              r0x     = if_else(xge075t, dec(x), r0x);
              r0z     = if_else(xge075t, one(as<T>()), r0z);
              r0s     = if_else(xge075t, mone(as<T>()), r0s);
              p       = lgammaC(r0x);
            }
            // tx < 1.5 && x < 0.75
            auto txlt150 = logical_andnot(is_less(tx, _150), xge075);
            if( eve::any(txlt150) )
            {
              auto orig = txlt150;
              while( eve::any(txlt150) )
              {
                z       = if_else(txlt150, z * tx, z);
                nx      = inc[txlt150](nx);
                tx      = if_else(txlt150, x + nx, tx);
                txlt150 = logical_andnot(is_less(tx, _150), xge075);
              }
              r0x = add[orig](r0x, nx - T(2));
              r0z = if_else(orig, z, r0z);
              r0s = if_else(orig, mone(as<T>()), r0s);
            }
            p = if_else(kernelC, p, lgammaB(r0x));
            if( nb >= cardinal_v<T> ) return fma(r0x, p, r0s * log(abs(r0z)));
          }
          r0z  = if_else(xlt650, abs(r0z), x);
          T m  = log(r0z);
          r1   = fma(r0x, p, r0s * m);
          T r2 = fma(x - half(as<T>()), m, Logsqrt2pi - x);
          r2 += lgamma2(rec(sqr(x))) / x;
          return if_else(xlt650, r1, r2);
        };
        T r1 = other(q);
        if( nb > 0 ) // some are negative
        {
          auto negative = [](T q, T w)
          {
            T    p     = floor(q);
            T    z     = q - p;
            auto test2 = (z < half(as<T>()));
            z          = dec[test2](z);
            z          = q * sinpi(z);
            z          = abs(z);
            return -log(inv_pi(as<T>()) * abs(z)) - w;
          };
          // treat negative
          r = if_else(inf_result, inf(as<T>()), negative(q, r1));
          if( nb >= cardinal_v<T> ) return r;
        }
        T r2 = if_else(ltza0, r, r1);
        return if_else(inf_result, inf(as<T>()), r2);
      }
    }
    else if constexpr( std::is_same_v<elt_t, double> ) // double
    {
      const T Logpi = T(1.1447298858494001741434273513530587116472948129153);
      if constexpr( scalar_value<T> ) // scalar double
      {
        const T Maxlgamma =
            Ieee_constant<T, 0x7bc3f8eaU, 0x7f574c5dd06d2516ULL>(); // 2.035093e36f, 2.556348e305
        auto lgamma_pos = [Logsqrt2pi](T x)
        {
          if( x < 13.0 )
          {
            T z = one(as<T>());
            T p = zero(as<T>());
            T u = x;
            while( u >= 3.0 )
            {
              p -= 1.0;
              u = x + p;
              z *= u;
            }
            while( u < 2.0 )
            {
              if( u == 0.0 ) return inf(as<T>());
              z /= u;
              p += 1.0;
              u = x + p;
            }
            z = abs(z);
            if( u == 2.0 ) return (log(z));
            p -= 2.0;
            x = x + p;
            p = x * lgamma1(x);
            return log(z) + p;
          }
          T q = fma((x - 0.5), log(x), Logsqrt2pi - x);
          if( x > 1.0e8 ) return q;

          T p = rec(sqr(x));
          q += lgammaA(p) / x;
          return q;
        };
        if( is_infinite(a0) || is_eqz(a0) ) return inf(as<T>()); // 2.556348e305
        T x = a0;
        T q = abs(x);
        if( x > Maxlgamma ) return inf(as<T>());
        if( x < -34.0 )
        {
          if( q > Maxlgamma ) return nan(as<T>());
          T w = lgamma_pos(q);
          T p = floor(q);
          if( p == q ) return inf(as<T>());
          T z = q - p;
          if( z > half(as<T>()) )
          {
            p += one(as<T>());
            z = p - q;
          }
          z = q * sinpi(z);
          if( is_eqz(z) ) return inf(as<T>());
          return Logpi - log(z) - w;
        }
        else { return lgamma_pos(x); }
      }
      else if constexpr( simd_value<T> ) // simd double
      {
        auto other = [Logsqrt2pi](T xx)
        {
          T              x    = xx;
          auto           test = (x < T(13.0));
          std::ptrdiff_t nb   = eve::count_true(test);
          T              r1   = zero(as<T>());
          if( nb > 0 )
          {
            T    z     = one(as<T>());
            T    p     = zero(as<T>());
            T    u     = if_else(test, x, eve::zero);
            auto test1 = (u > T(3));
            while( eve::any(test1) )
            {
              p     = dec[test1](p);
              u     = if_else(test1, x + p, u);
              z     = if_else(test1, z * u, z);
              test1 = (u >= T(3));
            }
            // all u are less than 3
            auto test2 = (u < T(2));

            while( eve::any(test2) )
            {
              z     = if_else(test2, z / u, z);
              p     = inc[test2](p);
              u     = if_else(test2, x + p, u);
              test2 = (u < T(2));
            }
            z = abs(z);
            x += p - T(2);
            r1 = x * lgamma1(x) + log(z);
            if( nb >= T::size() ) return r1;
          }
          T r2 = fma(xx - half(as<T>()), log(xx), Logsqrt2pi - xx);
          T p  = rec(sqr(xx));
          r2 += lgammaA(p) / xx;
          return if_else(test, r1, r2);
        };
        auto inf_result = (is_lez(a0) && is_flint(a0)) || is_infinite(a0);
        ;
        T x = if_else(inf_result, eve::allbits, a0);
        T q = abs(x);
        if( eve::platform::supports_infinites ) inf_result = inf_result || (q == inf(as<T>()));
        auto test = (a0 < T(-34.0));
        auto nb   = eve::count_true(test);
        T    r    = nan(as<T>());
        if( nb > 0 )
        {
          // treat negative large with reflection
          r = large_negative(q);
          if( nb >= T::size() ) return if_else(inf_result, inf(as<T>()), r);
        }
        T r1 = other(a0);
        T r2 = if_else(test, r, r1);
        return if_else(inf_result, inf(as<T>()), r2);
      }
    }
  }
  else return apply_over(lgamma, a0);
}
}
