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

namespace eve::detail
{
template<floating_ordered_value T>
EVE_FORCEINLINE T
cyl_bessel_k1_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  using elt_t = element_type_t<T>;
  if constexpr( has_native_abi_v<T> )
  {
    auto br_1 = [](auto x) // 0 1
    {
      if constexpr( std::same_as<elt_t, float> )
      {
        T                              y(8.695471287e-02f);
        using A3 = kumi::result::generate_t<3, elt_t>;
        constexpr A3 P = {
          -3.621379531e-03f
          , 7.131781976e-03f
          , -1.535278300e-05f
        };
        constexpr A3 Q = {
          1.000000000e+00f
          , -5.173102701e-02f
          , 9.203530671e-04f
        };
        T                              a = sqr(x / 2);
        a = ((reverse_horner(a, P)/reverse_horner(a, Q) + y) * sqr(a) + a / 2 + 1) * x / 2;
        using A4 = kumi::result::generate_t<4, elt_t>;
        constexpr A4 P2 = {
            -3.079657469e-01f
            , -8.537108913e-02f
            , -4.640275408e-03f
            , -1.156442414e-04f
        };
        return reverse_horner(sqr(x), P2) * x + rec(x) + log(x) * a;
      }
      else
      {
        T                              y(8.69547128677368164e-02);
        using A4 = kumi::result::generate_t<4, elt_t>;
        constexpr A4 P = {
          -3.62137953440350228e-03,
          7.11842087490330300e-03,
          1.00302560256614306e-05,
          1.77231085381040811e-06};
        constexpr A4 Q = {
          1.00000000000000000e+00,
          -4.80414794429043831e-02,
          9.85972641934416525e-04,
          -8.91196859397070326e-06};

        T a = sqr(x / 2);
        a   = ((reverse_horner(a, P)/reverse_horner(a, Q) + y) * sqr(a) + a / 2 + 1) * x / 2;

        constexpr A4 P2 = {
          -3.07965757829206184e-01,
          -7.80929703673074907e-02,
          -2.70619343754051620e-03,
          -2.49549522229072008e-05};
        constexpr A4 Q2 = {
          1.00000000000000000e+00,
          -2.36316836412163098e-02,
          2.64524577525962719e-04,
          -1.49749618004162787e-06
        };
        auto x2 = sqr(x);
        return (reverse_horner(x2, P2)/reverse_horner(x2, Q2)) * x + rec(x) + log(x) * a;
      }
    };

    auto br_large = [](auto x) // 1 infty
    {
      if constexpr( std::same_as<elt_t, float> )
      {
        auto                           y(1.450342178f);
        using A4 = kumi::result::generate_t<4, elt_t>;
        constexpr A4 P = {
            -1.970280088e-01f
            , 2.188747807e-02f
            , 7.270394756e-01f
            , 2.490678196e-01f
        };
        constexpr A4 Q = {
            1.000000000e+00f
            , 2.274292882e+00f
            , 9.904984851e-01f
            , 4.585534549e-02f
        };
        auto r = rec(x);
        if( eve::all(x < maxlog(as(x))) )
          return ((reverse_horner(r, P)/reverse_horner(r, Q) + y) * exp(-x) * rsqrt(x));
        else
        {
          T ex = exp(-x / 2);
          return ((reverse_horner(r, P)/reverse_horner(r, Q) + y) * ex * rsqrt(x)) * ex;
        }
      }
      else
      {
        auto                           y(1.45034217834472656);
        using A9 = kumi::result::generate_t<9, elt_t>;
        constexpr A9 P = {-1.97028041029226295e-01,
                -2.32408961548087617e+00,
                -7.98269784507699938e+00,
                -2.39968410774221632e+00,
                3.28314043780858713e+01,
                5.67713761158496058e+01,
                3.30907788466509823e+01,
                6.62582288933739787e+00,
                3.08851840645286691e-01};
        constexpr A9 Q = {1.00000000000000000e+00,
                1.41811409298826118e+01,
                7.35979466317556420e+01,
                1.77821793937080859e+02,
                2.11014501598705982e+02,
                1.19425262951064454e+02,
                2.88448064302447607e+01,
                2.27912927104139732e+00,
                2.50358186953478678e-02};
        auto                           r = rec(x);
        if( eve::all(x < maxlog(as(x))) )
          return ((reverse_horner(r, P)/reverse_horner(r, Q) + y) * exp(-x) * rsqrt(x));
        else
        {
          T ex = exp(-x / 2);
          return ((reverse_horner(r, P)/reverse_horner(r, Q) + y) * ex * rsqrt(x)) * ex;
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
  else return apply_over(cyl_bessel_k1, x);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, typename ... Ts>
EVE_FORCEINLINE auto
cyl_bessel_k1_(EVE_SUPPORTS(cpu_), C const& cond, Ts ... ts) noexcept
{
  return mask_op(cond, eve::cyl_bessel_k1, ts ...);
}

template<conditional_expr C, decorator D, typename  ... Ts>
EVE_FORCEINLINE auto
cyl_bessel_k1_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, Ts ... ts) noexcept
{
  return mask_op(cond, d(eve::cyl_bessel_k1), ts ...);
}
}
