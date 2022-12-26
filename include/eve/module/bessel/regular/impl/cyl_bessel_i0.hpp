//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <array>

namespace eve::detail
{
template<floating_ordered_value T>
EVE_FORCEINLINE T
cyl_bessel_i0_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  using elt_t = element_type_t<T>;
  if constexpr( has_native_abi_v<T> )
  {
    auto br_7_75 = [](auto x)
    {
      if constexpr( std::same_as<elt_t, float> )
      {
      using A9 = kumi::result::generate_t<9, elt_t>;
      static const A9 P = {1.00000003928615375e+00f,
                           2.49999576572179639e-01f,
                           2.77785268558399407e-02f,
                           1.73560257755821695e-03f,
                           6.96166518788906424e-05f,
                           1.89645733877137904e-06f,
                           4.29455004657565361e-08f,
                           3.90565476357034480e-10f,
                           1.48095934745267240e-11f};
      T                              a = sqr(x / 2);
      return inc(a * reverse_horner(a, P));
      }
      else
      {
        using A15 = kumi::result::generate_t<15, elt_t>;
        static const A15 P = {1.00000000000000000e+00,
                              2.49999999999999909e-01,
                              2.77777777777782257e-02,
                              1.73611111111023792e-03,
                              6.94444444453352521e-05,
                              1.92901234513219920e-06,
                              3.93675991102510739e-08,
                              6.15118672704439289e-10,
                              7.59407002058973446e-12,
                              7.59389793369836367e-14,
                              6.27767773636292611e-16,
                              4.34709704153272287e-18,
                              2.63417742690109154e-20,
                              1.13943037744822825e-22,
                              9.07926920085624812e-25};
        T                               a = sqr(x / 2);
        return inc(a * reverse_horner(a, P));
      }
    };

    auto br_medium = [](auto x) // float 50 double 500
      {
        if constexpr( std::same_as<elt_t, float> )
        {
          using A5 = kumi::result::generate_t<5, elt_t>;
          static const A5 P = {3.98942651588301770e-01f,
                             4.98327234176892844e-02f,
                             2.91866904423115499e-02f,
                             1.35614940793742178e-02f,
                             1.31409251787866793e-01f};
          return eve::exp(x) * reverse_horner(rec(x), P) * eve::rsqrt(x);
        }
        else
        {
          using A22 = kumi::result::generate_t<22, elt_t>;
          static const A22 P = {
            3.98942280401425088e-01,  4.98677850604961985e-02,  2.80506233928312623e-02,
            2.92211225166047873e-02,  4.44207299493659561e-02,  1.30970574605856719e-01,
            -3.35052280231727022e+00, 2.33025711583514727e+02,  -1.13366350697172355e+04,
            4.24057674317867331e+05,  -1.23157028595698731e+07, 2.80231938155267516e+08,
            -5.01883999713777929e+09, 7.08029243015109113e+10,  -7.84261082124811106e+11,
            6.76825737854096565e+12,  -4.49034849696138065e+13, 2.24155239966958995e+14,
            -8.13426467865659318e+14, 2.02391097391687777e+15,  -3.08675715295370878e+15,
            2.17587543863819074e+15};
          return eve::exp(x) * reverse_horner(rec(x), P) * eve::rsqrt(x);
        }
      };

    auto br_large = [](auto x)
      {
        if constexpr( std::same_as<elt_t, float> )
        {
          using A3 = kumi::result::generate_t<3, elt_t>;
          static const A3 P = {
            3.98942391532752700e-01f
            , 4.98455950638200020e-02f
            , 2.94835666900682535e-02f}
          ;
          auto ex = eve::exp(x / 2);
          return ex * (ex * reverse_horner(rec(x), P) / eve::sqrt(x));
        }
        else
        {
          using A5 = kumi::result::generate_t<5, elt_t>;
          static const A5 P  = {3.98942280401432905e-01,
                                4.98677850491434560e-02,
                                2.80506308916506102e-02,
                                2.92179096853915176e-02,
                                4.53371208762579442e-02};
          auto                           ex = eve::exp(x / 2);
          return ex * (ex * reverse_horner(rec(x), P) * eve::rsqrt(x));
        }
      };

    if constexpr( scalar_value<T> )
    {
      if( is_ngez(x) ) return nan(as(x));
      if( x == 0 ) return zero(as(x));         // x is 0
      if( x == inf(as(x)) ) return inf(as(x)); // x is infinite
      if( x < T(7.75) ) return br_7_75(x);     // x in (0, 7.75]
      const auto thresh = if_else(std::same_as<elt_t, float>, elt_t(50), elt_t(500));
      if( x < thresh ) return br_medium(x); // x in (7.75, thresh]
      return br_large(x);                   // x in (thresh, \infty)
    }
    else
    {
      if constexpr( has_native_abi_v<T> )
      {
        auto r       = nan(as(x));
        auto notdone = is_nltz(x);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_7_75, notdone, x <= T(7.75), r, x);
          if( eve::any(notdone) )
          {
            const auto thresh = if_else(std::same_as<elt_t, float>, elt_t(50), elt_t(500));
            notdone           = next_interval(br_medium, notdone, x <= T(thresh), r, x);
            if( eve::any(notdone) ) { notdone = last_interval(br_large, notdone, r, x); }
          }
        }
        r = if_else(is_eqz(x), zero(as(x)), r);
        r = if_else(x == inf(as(x)), inf, r);
        return r;
      }
    }
  }
  else return apply_over(cyl_bessel_i0, x);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, typename ... Ts>
EVE_FORCEINLINE auto
cyl_bessel_i0_(EVE_SUPPORTS(cpu_), C const& cond, Ts ... ts) noexcept
{
  return mask_op(cond, eve::cyl_bessel_i0, ts ...);
}

template<conditional_expr C, decorator D, typename  ... Ts>
EVE_FORCEINLINE auto
cyl_bessel_i0_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, Ts ... ts) noexcept
{
  return mask_op(cond, d(eve::cyl_bessel_i0), ts ...);
}
}
