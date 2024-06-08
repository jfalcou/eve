//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/math.hpp>

namespace eve
{
  template<typename Options>
  struct log_abs_gamma_t : elementwise_callable<log_abs_gamma_t, Options>
  {
    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE constexpr
    T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(log_abs_gamma_t, log_abs_gamma_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var log_abs_gamma
//!   @brief Computes the natural logarithm of the absolute value of the \f$\Gamma\f$ function.
//!
//!   **Defined in header**
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
//!      template< eve::floating_value T >
//!      T log_abs_gamma(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real argument](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   In the two cases, the value of the  logarithm of the absolute value of the \f$\Gamma\f$ function is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/log_abs_gamma.cpp}
//! @}
//================================================================================================
inline constexpr auto log_abs_gamma = functor<log_abs_gamma_t>;

  namespace detail
  {
    namespace helpers
    {
      template<floating_ordered_value T>  constexpr EVE_FORCEINLINE T large_negative(T q)
      {
        T    w     = eve::log_abs_gamma(q);
        T    p     = floor(q);
        T    z     = q - p;
        auto test2 = (z < half(as<T>()));
        z          = dec[test2](z);
        z          = q * sinpi(z);
        z          = abs(z);
        return T(1.1447298858494001741434273513530587116472948129153) - log(z) - w;
      }

      template<floating_ordered_value T> constexpr EVE_FORCEINLINE T log_abs_gammaB(T x) noexcept
      {
        // log gamma(x+2), -.5 < x < .5
        return
          eve::reverse_horner(x, T(0x1.b0ee60p-2f), T(0x1.4a34c8p-2f), T(-0x1.13e0fcp-4f), T(0x1.513db0p-6f)
                             , T(-0x1.e2c9fap-8f), T(0x1.775106p-9f), T(-0x1.57d562p-10f), T(0x1.3d7728p-11f));
      }

      template<floating_ordered_value T> constexpr EVE_FORCEINLINE T log_abs_gammaC(T x) noexcept
      {
        // log gamma(x+1), -.25 < x < .25
        return
          eve::reverse_horner(x, T(-0x1.2788d0p-1f), T(0x1.a51a68p-1f), T(-0x1.9a4f50p-2f), T(0x1.151316p-2f)
                             , T(-0x1.a7809ep-3f), T(0x1.5a9b56p-3f), T(-0x1.45a652p-3f), T(0x1.18789ep-3f));
      }

      template<floating_ordered_value T> constexpr EVE_FORCEINLINE T log_abs_gamma2(T p) noexcept
      {
        return  eve::reverse_horner(p, T(0x1.555528p-4f), T(-0x1.6b0e02p-9f), T(0x1.63fad2p-11f));
      }

      template<floating_ordered_value T>
      constexpr EVE_FORCEINLINE T
      log_abs_gamma1(T x) noexcept
      {
        return eve::reverse_horner(x, T(-0x1.a0c675418055ep+19), T(-0x1.a45890219f20bp+20), T(-0x1.1bc82f994db51p+20)
                                  , T(-0x1.43d73f89089e5p+18), T(-0x1.2f234355bb93ep+15), T(-0x1.589018ff36761p+10))/
          eve::reverse_horner(x, T(-0x1.ece4b6a11e14ap+20), T(-0x1.35255892ff34cp+21), T(-0x1.1628671950043p+20)
                             , T(-0x1.aeb84b9744c9bp+17), T(-0x1.0aa0d7b89d757p+14), T(-0x1.5fd0d1cf312b2p+8)
                             , T(0x1.0000000000000p+0));
      }

      template<floating_ordered_value T> constexpr EVE_FORCEINLINE T log_abs_gammaA(const T& p) noexcept
      {
        return
          eve::reverse_horner(p, T(0x1.555555555554bp-4), T(-0x1.6c16c16b0a5a1p-9), T(0x1.a019f20dc5ebbp-11)
                             , T(-0x1.37fbdb580e943p-11), T(0x1.a985027336661p-11));
      }
    }

    template<typename T, callable_options O>
    constexpr T
    log_abs_gamma_(EVE_REQUIRES(cpu_), O const&, T a0) noexcept
    {
      const T Logsqrt2pi = T(0.91893853320467274178032973640561763986139747363777);
      using elt_t        = element_type_t<T>;
      if constexpr( std::is_same_v<elt_t, float> )
      {
        if constexpr( scalar_value<T> )
        {
          if( (is_infinite(a0)) ) return inf(as<T>());
          const T Maxlog_abs_gamma = ieee_constant<0x1.87f1d40p+120f, 0x1.74c5dd06d2516p+1014>(eve::as<T>{});
          auto log_abs_gamma_pos = [Logsqrt2pi](T x)
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
                  T p = x * helpers::log_abs_gammaB(x);
                  return p + log(z);
                }
                if( x >= 1.25f )
                {
                  z *= x;
                  x   = dec(x);
                  T p = x * helpers::log_abs_gammaB(x);
                  return p - log(z);
                }
                if( x >= 0.75f )
                {
                  x = dec(x);
                  return x * helpers::log_abs_gammaC(x);
                }
                while( tx < 1.5f )
                {
                  if( is_eqz(tx) ) return inf(as<T>());
                  z *= tx;
                  nx = inc(nx);
                  tx = x + nx;
                }
                x += nx - T(2);
                T p = x * helpers::log_abs_gammaB(x);
                return p - log(z);
              }
              T q = fma((x - 0.5f), log(x), Logsqrt2pi - x);
              if( x <= 1.0e4f )
              {
                T z = rec[pedantic2](x);
                T p = sqr(z);
                q   = fma(z, helpers::log_abs_gamma2(p), q);
              }
              return q;
            };

          if( (a0 > Maxlog_abs_gamma) || is_eqz(a0) ) return inf(as<T>());
          T x = a0;
          T q = abs(x);
          if( x < 0.0f )
          {
            if( q > Maxlog_abs_gamma ) return nan(as<T>());
            T w = log_abs_gamma_pos(q);
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
          else { return log_abs_gamma_pos(x); }
        }
        else if constexpr( simd_value<T> )
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


                auto xge125  = (x >= _125);
                auto xge125t = logical_andnot(xge125, xge150);
                if( eve::any(xge125) )
                {
                  r0x = if_else(xge125t, dec(x), r0x);
                  r0z = if_else(xge125t, z * x, r0z);
                  r0s = if_else(xge125t, mone(as<T>()), r0s);
                }

                auto xge075  = (x >= _075);
                auto xge075t = logical_andnot(xge075, xge125);
                if( eve::any(xge075t) )
                {
                  kernelC = xge075t;
                  r0x     = if_else(xge075t, dec(x), r0x);
                  r0z     = if_else(xge075t, one(as<T>()), r0z);
                  r0s     = if_else(xge075t, mone(as<T>()), r0s);
                  p       = helpers::log_abs_gammaC(r0x);
                }

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
                p = if_else(kernelC, p, helpers::log_abs_gammaB(r0x));
                if( nb >= cardinal_v<T> ) return fma(r0x, p, r0s * log(abs(r0z)));
              }
              r0z  = if_else(xlt650, abs(r0z), x);
              T m  = log(r0z);
              r1   = fma(r0x, p, r0s * m);
              T r2 = fma(x - half(as<T>()), m, Logsqrt2pi - x);
              r2 += helpers::log_abs_gamma2(rec[pedantic2](sqr(x))) / x;
              return if_else(xlt650, r1, r2);
            };
          T r1 = other(q);
          if( nb > 0 )
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
      else if constexpr( std::is_same_v<elt_t, double> )
      {
        const T Logpi = T(1.1447298858494001741434273513530587116472948129153);
        if constexpr( scalar_value<T> )
        {
          const T Maxlog_abs_gamma =
            ieee_constant<0x1.87f1d40p+120f, 0x1.74c5dd06d2516p+1014>(eve::as<T>{});
          auto log_abs_gamma_pos = [Logsqrt2pi](T x)
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
                p = x * helpers::log_abs_gamma1(x);
                return log(z) + p;
              }
              T q = fma((x - 0.5), log(x), Logsqrt2pi - x);
              if( x > 1.0e8 ) return q;

              T p = rec[pedantic2](sqr(x));
              q += helpers::log_abs_gammaA(p) / x;
              return q;
            };
          if( is_infinite(a0) || is_eqz(a0) ) return inf(as<T>());
          T x = a0;
          T q = abs(x);
          if( x > Maxlog_abs_gamma ) return inf(as<T>());
          if( x < -34.0 )
          {
            if( q > Maxlog_abs_gamma ) return nan(as<T>());
            T w = log_abs_gamma_pos(q);
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
          else { return log_abs_gamma_pos(x); }
        }
        else if constexpr( simd_value<T> )
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
                r1 = x * helpers::log_abs_gamma1(x) + log(z);
                if( nb >= T::size() ) return r1;
              }
              T r2 = fma(xx - half(as<T>()), log(xx), Logsqrt2pi - xx);
              T p  = rec[pedantic2](sqr(xx));
              r2 += helpers::log_abs_gammaA(p) / xx;
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
            r = helpers::large_negative(q);
            if( nb >= T::size() ) return if_else(inf_result, inf(as<T>()), r);
          }
          T r1 = other(a0);
          T r2 = if_else(test, r, r1);
          return if_else(inf_result, inf(as<T>()), r2);
        }
      }
    }
  }
}
