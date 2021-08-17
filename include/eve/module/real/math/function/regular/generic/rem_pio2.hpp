//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/twoopi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/load.hpp>
#include <eve/module/real/math/detail/scalar/ieee_754_rem_pio2.hpp>
#include <eve/traits/alignment.hpp>
#include <type_traits>

// This function object is an old slow version whose only purpose is to test the new version
// contained in rempio2

namespace eve::detail
{
  template<floating_real_simd_value T>
  EVE_FORCEINLINE auto rem_pio2_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    using elt_t = element_type_t<T>;

    constexpr uint32_t size = cardinal_v<T>;
    constexpr auto algt = alignment_v<T>;

    alignas(algt) std::array<elt_t, size> tmp;
    alignas(algt) std::array<elt_t, size> txr;
    alignas(algt) std::array<elt_t, size> tyr;
    for( uint32_t i = 0; i != size; ++i )
    {
      kumi::tie(tmp[i], txr[i], tyr[i]) = eve::rem_pio2(a0.get(i));
    }

    return kumi::make_tuple( eve::load(eve::as_aligned(&tmp[0]), cardinal_t<T>{})
                          , eve::load(eve::as_aligned(&txr[0]), cardinal_t<T>{})
                          , eve::load(eve::as_aligned(&tyr[0]), cardinal_t<T>{})
                          );
  }

  EVE_FORCEINLINE auto rem_pio2_(EVE_SUPPORTS(cpu_), double const &a0) noexcept
  {
    if( a0 == inf(eve::as<double>()) )
      return kumi::make_tuple(zero(eve::as<double>()), nan(eve::as<double>()), nan(eve::as<double>()));
    double       y[2];
    std::int32_t n = __ieee754_rem_pio2(a0, y);
    return kumi::make_tuple(static_cast<double>(n & std::int32_t(3)), y[0], y[1]);
  }

  EVE_FORCEINLINE auto rem_pio2_(EVE_SUPPORTS(cpu_), float const &a0) noexcept
  {
    if( a0 == inf(eve::as<float>()) )
      return kumi::make_tuple(zero(eve::as<float>()), nan(eve::as<float>()), nan(eve::as<float>()));
    // This is the musl way
    // pio2_1:   first 25 bits of pi/2
    // pio2_1t:  pi/2 - pio2_1
    //
    static const double pio2_1 = 1.57079631090164184570e+00, /* 0x3FF921FB, 0x50000000 */
        pio2_1t                = 1.58932547735281966916e-08; /* 0x3E5110b4, 0x611A6263 */
    if( abs(a0) < 4.2166e+08 )                               /* |x| ~< 2^28*(pi/2), medium size */
    {
      /* 25+53 bit pi is good enough for medium size */
      double fn = nearest(double(a0) * twoopi(eve::as<double>()));
      return kumi::make_tuple(static_cast<float>(quadrant(fn)),
                             static_cast<float>((a0 - fn * pio2_1) - fn * pio2_1t),
                             0.0f);
    }
    auto [fn, x, dx] = rem_pio2(double(a0));
    float fx         = static_cast<float>(x);
    return kumi::make_tuple(static_cast<float>(fn), fx, 0.0f);
  }
}
