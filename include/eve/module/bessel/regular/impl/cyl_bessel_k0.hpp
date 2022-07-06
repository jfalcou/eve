//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/bessel/detail/evaluate_rational.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <array>

namespace eve::detail
{
template<floating_real_value T>
EVE_FORCEINLINE T
cyl_bessel_k0_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  using elt_t = element_type_t<T>;
  if constexpr( has_native_abi_v<T> )
  {
    auto br_1 = [](auto x) // 0 1
    {
      T y(1.137250900268554688);
      if constexpr( std::same_as<elt_t, float> )
      {
        constexpr std::array<elt_t, 3> P = {
            -1.372508979104259711e-01f, 2.622545986273687617e-01f, 5.047103728247919836e-03f};
        constexpr std::array<elt_t, 3> Q = {
            1.000000000000000000e+00f, -8.928694018000029415e-02f, 2.985980684180969241e-03f};
        T a                               = sqr(x / 2);
        a                                 = inc((evaluate_rational(P, Q, a) + y) * a);
        constexpr std::array<elt_t, 5> P2 = {1.159315158e-01f,
                                             2.789828686e-01f,
                                             2.524902861e-02f,
                                             8.457241514e-04f,
                                             1.530051997e-05f};
        return reverse_horner(sqr(x), P2) - log(x) * a;
        return a;
      }
      else
      {
        T                              y(1.137250900268554688);
        constexpr std::array<elt_t, 5> P = {-1.372509002685546267e-01,
                                            2.574916117833312855e-01,
                                            1.395474602146869316e-02,
                                            5.445476986653926759e-04,
                                            7.125159422136622118e-06};
        constexpr std::array<elt_t, 4> Q = {1.000000000000000000e+00,
                                            -5.458333438017788530e-02,
                                            1.291052816975251298e-03,
                                            -1.367653946978586591e-05};

        T a = sqr(x / 2);
        a   = inc((reverse_horner(a, P) / reverse_horner(a, Q) + y) * a);

        constexpr std::array<elt_t, 8> P2 = {1.159315156584124484e-01,
                                             2.789828789146031732e-01,
                                             2.524892993216121934e-02,
                                             8.460350907213637784e-04,
                                             1.491471924309617534e-05,
                                             1.627106892422088488e-07,
                                             1.208266102392756055e-09,
                                             6.611686391749704310e-12};
        return reverse_horner(sqr(x), P2) - eve::log(x) * a;
      }
    };

    auto br_large = [](auto x) // 1 infty
    {
      if constexpr( std::same_as<elt_t, float> )
      {
        constexpr std::array<elt_t, 4> P = {
            2.533141220e-01f, 5.221502603e-01f, 6.380180669e-02f, -5.934976547e-02f};
        constexpr std::array<elt_t, 4> Q = {
            1.000000000e+00f, 2.679722431e+00f, 1.561635813e+00f, 1.573660661e-01f};
        auto r = rec(x);
        if( eve::all(x < maxlog(as(x))) )
          return (inc(evaluate_rational(P, Q, r)) * exp(-x) * rsqrt(x));
        else
        {
          T ex = exp(-x / 2);
          return (inc(evaluate_rational(P, Q, r)) * ex * rsqrt(x)) * ex;
        }
      }
      else
      {
        constexpr std::array<elt_t, 9> P = {2.533141373155002416e-01,
                                            3.628342133984595192e+00,
                                            1.868441889406606057e+01,
                                            4.306243981063412784e+01,
                                            4.424116209627428189e+01,
                                            1.562095339356220468e+01,
                                            -1.810138978229410898e+00,
                                            -1.414237994269995877e+00,
                                            -9.369168119754924625e-02};
        constexpr std::array<elt_t, 9> Q = {1.000000000000000000e+00,
                                            1.494194694879908328e+01,
                                            8.265296455388554217e+01,
                                            2.162779506621866970e+02,
                                            2.845145155184222157e+02,
                                            1.851714491916334995e+02,
                                            5.486540717439723515e+01,
                                            6.118075837628957015e+00,
                                            1.586261269326235053e-01};
        auto                           r = rec(x);
        if( eve::all(x < maxlog(as(x))) )
          return (inc(evaluate_rational(P, Q, r)) * exp(-x) * rsqrt(x));
        else
        {
          T ex = exp(-x / 2);
          return (inc(evaluate_rational(P, Q, r)) * ex * rsqrt(x)) * ex;
        }
      }
    };

    if constexpr( scalar_value<T> )
    {
      if( is_ngez(x) ) return nan(as(x));
      if( x == 0 ) return inf(as(x));           // x is 0
      if( x == inf(as(x)) ) return zero(as(x)); // x is infinite
      if( x < one(as(x)) ) return br_1(x);      // x in (0, 1]
      return br_large(x);                       // x in (t1, \infty)
    }
    else
    {
      if constexpr( has_native_abi_v<T> )
      {
        auto r       = nan(as(x));
        auto notdone = is_gtz(x);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_1, notdone, x <= T(1), r, x);
          if( eve::any(notdone) ) { notdone = last_interval(br_large, notdone, r, x); }
        }
        r = if_else(is_eqz(x), inf(as(x)), r);
        r = if_else(x == inf(as(x)), zero, r);
        return r;
      }
    }
  }
  else return apply_over(cyl_bessel_k0, x);
}
}
