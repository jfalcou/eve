//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/bessel/regular/cyl_bessel_jn.hpp>
#include <eve/module/bessel/regular/cyl_bessel_kn.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{
template<floating_ordered_value T>
EVE_FORCEINLINE T
airy_ai_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  using elt_t = element_type_t<T>;
  auto ax     = eve::abs(x);
  T    rac    = eve::sqrt(ax);
  T    p      = (ax * rac * 2) / 3;
  T    v      = T(1.0 / 3);
  auto br_0   = [v, p, rac]()
  {
    T j1 = cyl_bessel_jn(v, p);
    T j2 = cyl_bessel_jn(-v, p);
    return rac * (j1 + j2) / 3;
  };
  auto br_small = []() { return T(0.355028053887817); };
  auto br_last  = [v, p, rac]()
  {
    return cyl_bessel_kn(v, p) * rac * T(0.183776298473931); // third *inv_pi(as(p));
  };
  elt_t constexpr thresh = (sizeof(elt_t) == 8) ? (4.440892098500626e-16) : (2.3841858e-07);
  if constexpr( scalar_value<T> )
  {
    if( x == minf(as(x)) ) return zero(as(x));
    if( is_nan(x) ) return nan(as(x));
    if( x == inf(as(x)) ) return zero(as(x));
    if( x < 0 ) return br_0();
    if( x < thresh ) return br_small();
    return br_last();
  }
  else
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto r       = nan(as(x));
      auto notdone = is_not_nan(x);
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_0, notdone, is_ltz(x), r);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_small, notdone, x < thresh, r);
          if( eve::any(notdone) ) { last_interval(br_last, notdone, r); }
        }
      }
      r = if_else(is_infinite(x), zero, r);
      return r;
    }
    else return apply_over(airy_ai, x);
  }
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, typename ... Ts>
EVE_FORCEINLINE auto
airy_ai_(EVE_SUPPORTS(cpu_), C const& cond, Ts ... ts) noexcept
{
  return mask_op(cond, eve::airy_ai, ts ...);
}

template<conditional_expr C, decorator D, typename  ... Ts>
EVE_FORCEINLINE auto
airy_ai_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, Ts ... ts) noexcept
{
  return mask_op(cond, d(eve::airy_ai), ts ...);
}
}
