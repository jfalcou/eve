//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_REM_PIO2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_REM_PIO2_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/twoopi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/load.hpp>
#include <eve/function/abs.hpp>
#include <eve/module/core/detail/scalar/ieee_754_rem_pio2.hpp>

#include <tuple>
#include <type_traits>

// This function object is an old slow version whose only purpose is to test the new version
// contained in rempio2

namespace eve::detail
{
  template<floating_real_simd_value T>
  EVE_FORCEINLINE auto rem_pio2_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    using elt_t = element_type_t<T>;

    static constexpr uint32_t                            size = cardinal_v<T>;
    alignas(T::static_alignment) std::array<elt_t, size> tmp;
    alignas(T::static_alignment) std::array<elt_t, size> txr;
    alignas(T::static_alignment) std::array<elt_t, size> tyr;
    for( uint32_t i = 0; i != size; ++i )
    { std::tie(tmp[i], txr[i], tyr[i]) = eve::rem_pio2(a0[i]); }
    return std::make_tuple(eve::load(eve::as_aligned<T::static_alignment>(&tmp[0]), eve::as_<T>()),
                           eve::load(eve::as_aligned<T::static_alignment>(&txr[0]), eve::as_<T>()),
                           eve::load(eve::as_aligned<T::static_alignment>(&tyr[0]), eve::as_<T>()));
  }

  EVE_FORCEINLINE auto rem_pio2_(EVE_SUPPORTS(cpu_), double const &a0) noexcept
  {
    if( a0 == Inf<double>() )
      return std::make_tuple(Zero<double>(), Nan<double>(), Nan<double>());
    double       y[2];
    std::int32_t n = __ieee754_rem_pio2(a0, y);
    return std::make_tuple(static_cast<double>(n & std::int32_t(3)), y[0], y[1]);
  }

  EVE_FORCEINLINE auto rem_pio2_(EVE_SUPPORTS(cpu_), float const &a0) noexcept
  {
    if( a0 == Inf<float>() )
      return std::make_tuple(Zero<float>(), Nan<float>(), Nan<float>());
    // This is the musl way
    // pio2_1:   first 25 bits of pi/2
    // pio2_1t:  pi/2 - pio2_1
    //
    static const double pio2_1 = 1.57079631090164184570e+00, /* 0x3FF921FB, 0x50000000 */
        pio2_1t                = 1.58932547735281966916e-08; /* 0x3E5110b4, 0x611A6263 */
    if( abs(a0) < 4.2166e+08 )                               /* |x| ~< 2^28*(pi/2), medium size */
    {
      /* 25+53 bit pi is good enough for medium size */
      double fn = nearest(double(a0) * Twoopi<double>());
      return std::make_tuple(static_cast<float>(quadrant(fn)),
                             static_cast<float>((a0 - fn * pio2_1) - fn * pio2_1t),
                             0.0f);
    }
    auto [fn, x, dx] = rem_pio2(double(a0));
    float fx         = static_cast<float>(x);
    return std::make_tuple(static_cast<float>(fn), fx, 0.0f);
  }
}

#endif
