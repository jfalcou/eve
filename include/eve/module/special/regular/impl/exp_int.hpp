//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/regular/tgamma.hpp>

namespace eve::detail
{
template<floating_real_value T>
EVE_FORCEINLINE T
exp_int_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  return exp_int(T(1), x);
}

template<scalar_value I, floating_real_scalar_value T>
EVE_FORCEINLINE T
exp_int_(EVE_SUPPORTS(cpu_), I in, T x) noexcept
{
  if( in == 0 ) return exp(-x) / x;
  if( in < 0 ) return nan(as<T>());
  return exp_int(T(in), x);
}

template<integral_scalar_value I, floating_real_simd_value T>
EVE_FORCEINLINE auto
exp_int_(EVE_SUPPORTS(cpu_), I in, T x) noexcept
//  requires compatible_values<T, I>
{
  using elt_t = element_type_t<T>;

  auto n = T(convert(in, as<elt_t>()));
  return exp_int(n, x);
}

template<integral_simd_value I, floating_real_simd_value T>
EVE_FORCEINLINE auto
exp_int_(EVE_SUPPORTS(cpu_), I in, T x) noexcept
//  requires compatible_values<T, I>
{
  using elt_t = element_type_t<T>;
  return exp_int(convert(in, as<elt_t>()), x);
}

template<integral_simd_value I, floating_real_scalar_value T>
EVE_FORCEINLINE auto
exp_int_(EVE_SUPPORTS(cpu_), I in, T x) noexcept
//  requires compatible_values<T, I>
{
  using elt_t = element_type_t<T>;
  using w_t   = wide<elt_t, cardinal_t<I>>;
  using i_t   = as_integer_t<elt_t>;
  return exp_int(convert(in, as<i_t>()), w_t(x));
}

template<floating_real_value T>
EVE_FORCEINLINE T
exp_int_(EVE_SUPPORTS(cpu_), T n, T x) noexcept
{
  using elt_t = element_type_t<T>;
  if constexpr( has_native_abi_v<T> )
  {
    auto notdone  = is_gez(x) && is_flint(n) && is_gez(n);
    T    r        = nan(as(x));  // if_else(notdone, zero, nan(as(x)));
    auto br_zeron = [](auto x) { // n == 0
      return exp(-x) / x;
    };
    notdone = next_interval(br_zeron, notdone, is_eqz(n), r, x); // n == 0
    if( eve::any(notdone) )
    {
      auto br_largen = [](auto n, auto x) { // n >  5000
        auto xk  = x + n;
        auto yk  = rec(sqr(xk));
        auto t   = n;
        auto ans = yk * t * (6 * sqr(x) - 8 * t * x + sqr(t));
        ans      = yk * (ans + t * (t - 2 * x));
        ans      = yk * (ans + t);
        return inc(ans) * exp(-x) / xk;
      };
      notdone = next_interval(br_largen, notdone, n > 5000, r, n, x); // n >  5000
      if( eve::any(notdone) )
      {
        auto br_xlt1 = [](auto n, auto x) { // here x is always le 1
          auto eqzx    = is_eqz(x);
          x            = inc[eqzx](x); // loop is infinite for x == 0
          auto    psi1 = zero(as(x));
          int32_t maxn = dec(max(1, int32_t(eve::maximum(n))));
          for( int32_t i = maxn; i != 0; --i ) psi1 = add[T(i) < n](psi1, rec(T(i)));
          auto euler = Ieee_constant<T, 0x3f13c468U, 0x3fe2788cfc6fb619ULL>();
          auto psi   = -euler - log(x) + psi1;
          T    t;
          ;
          auto z   = -x;
          auto xk  = zero(as(x));
          auto yk  = one(as(x));
          auto pk  = oneminus(n);
          auto ans = if_else(is_eqz(pk), zero, rec(pk));
          do {
            xk = inc(xk);
            yk *= z / xk;
            pk  = inc(pk);
            ans = add[is_nez(pk)](ans, yk / pk);
            t   = if_else(is_nez(ans), abs(yk / ans), one);
          }
          while( eve::any(t > epso_2(as(x))) );
          auto in = int_(n);
          return add[eqzx]((eve::pow(z, dec(in)) * psi / tgamma(n)) - ans, inf(as(x)));
        };
        auto xlt1 = x < 1;
        T    xx   = if_else(xlt1, x, one);
        notdone   = next_interval(br_xlt1, notdone, xlt1, r, n, xx); // x <  1
        if( eve::any(notdone) )
        {
          auto br_xge1 = [](auto n, auto x) { // here x is always gt 1
            auto    exp_intbig = (sizeof(elt_t) == 8) ? T(1ull << 57) : T(1ull << 24);
            auto    r          = exp_intbig;
            int32_t sk         = 1;
            T       t;
            auto    pkm2 = one(as(x));
            auto    qkm2 = x;
            auto    pkm1 = one(as(x));
            auto    qkm1 = x + n;
            auto    ans  = pkm1 / qkm1;
            do {
              auto stest = is_odd(T(++sk));
              auto k_2   = T(sk >> 1);
              auto yk    = if_else(stest, one, x);
              auto xk    = add[stest](k_2, n);
              auto pk    = pkm1 * yk + pkm2 * xk;
              auto qk    = qkm1 * yk + qkm2 * xk;
              r          = pk / qk;
              auto test  = is_nez(qk);
              t          = if_else(test, abs((ans - r) / r), one);
              ans        = if_else(test, r, ans);
              pkm2       = pkm1;
              pkm1       = pk;
              qkm2       = qkm1;
              qkm1       = qk;
              test       = abs(pk) > exp_intbig;
              auto fac   = if_else(test, epso_2(as(x)), one);
              pkm2 *= fac;
              pkm1 *= fac;
              qkm2 *= fac;
              qkm1 *= fac;
            }
            while( eve::any(t > eps(as(x))) );
            return add[x < maxlog(as(x))](zero(as(x)), ans * exp(-x));

          };
          T xx    = if_else(xlt1, T(2), x);
          notdone = last_interval(br_xge1, notdone, r, n, xx);
        }
      }
    }
    return if_else(is_eqz(x), rec(dec(n)), r);
  }
  else return apply_over(exp_int, n, x);
}
}
