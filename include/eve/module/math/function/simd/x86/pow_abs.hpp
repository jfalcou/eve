//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2020 Joel FALCOU
   Copyright 2020 Jean-Thierry LAPRESTE

   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/exp2.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/frexp.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/log.hpp>
#include <eve/function/log2.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/logical_andnot.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/minus.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/sqr.hpp>
#include <eve/module/math/detail/generic/pow_kernel.hpp>
#include <eve/platform.hpp>
#include <cmath>
#include <type_traits>

namespace eve::detail
{
  // this implementation is better only if we are in  avx_ or greater
  template< typename N>
  auto pow_abs_(EVE_SUPPORTS(avx_), wide<double, N, avx_> a, wide<double, N, avx_> b) noexcept
  {
    using v_t = wide<double, N, avx_>;
    const v_t Oneo_16 = v_t(0.0625);
    //        using i_t = as_integer_t<v_t>;
    v_t ax             = eve::abs(a);
    auto [xm, ee]    = pedantic_(frexp)(ax);
    auto [x, i]      = kernel_select(xm);
    v_t z              = sqr(x);
    v_t w              = kernel_pow1(x, z);
    w                = fma(Mhalf<v_t>(), z, w);
    const v_t Log2_em1 = v_t(0.44269504088896340735992468100189);
    w                = fma(Log2_em1, w, w);
    z                = fma(Log2_em1, x, w);
    z += x;
    w          = fnma(tofloat(i), Oneo_16, ee);
    auto reduc = [Oneo_16](v_t const & x) {
      // Find a multiple of 1/16 that is within 1/16 of x.
      return Oneo_16 * floor(v_t(16) * x);
    };
    v_t ya = reduc(b);
    v_t yb = b - ya;
    v_t W  = fma(z, b, w * yb);
    v_t Wa = reduc(W);
    v_t Wb = W - Wa;
    W    = fma(w, ya, Wa);
    Wa   = reduc(W);
    v_t u  = W - Wa;
    W    = Wb + u;
    Wb   = reduc(W);
    w    = v_t(16) * (Wa + Wb);
    // v_test the power of 2 for over/underflow
    const v_t Powlargelim = Ieee_constant<v_t, 0x44ffe000U, 0x40cfff8000000000ULL>();
    const v_t Powlowlim   = Ieee_constant<v_t, 0xc5160000U, 0xc0d0c7c000000000ULL>();
    auto    inf_ret     = is_greater(w, Powlargelim);
    auto    zer_ret     = is_less(w, Powlowlim);
    auto    e           = toint(w);
    Wb                  = W - Wb;
    auto test           = is_gtz(Wb);
    e                   = inc[test](e);
    Wb                  = sub[test](Wb, Oneo_16);
    z                   = kernel_pow2(Wb) * Wb;
    i                   = inc[is_gtz(e)](e / 16);
    e                   = fms(i, 16, e);
    w                   = twomio16(e);
    z                   = fma(w, z, w);
    z                   = pedantic_(ldexp)(z, i);
    if constexpr( eve::platform::supports_infinites )
    {
      auto gtax1 = is_greater(ax, One<v_t>());
      z          = if_else(is_equal(b, Inf<v_t>()), if_else(gtax1, Inf<v_t>(), eve::zero_), z);
      z          = if_else(is_equal(b, Minf<v_t>()), if_else(gtax1, eve::zero_, Inf<v_t>()), z);
      z = if_else(is_equal(ax, Inf<v_t>()), if_else(is_gtz(b), Inf<v_t>(), binarize(is_gez(b))), z);
    }
    z = if_else(zer_ret, eve::zero_, z);
    z = if_else(inf_ret, Inf<v_t>(), z);
    z = if_else(is_equal(ax, One<v_t>()), ax, z);

    z = if_else(is_eqz(a), if_else(is_ltz(b), eve::Inf<v_t>(), binarize(is_eqz(b))), z);
    if constexpr( eve::platform::supports_invalids )
    {
      z = if_else(is_nan(a), if_else(is_eqz(b), One<v_t>(), eve::allbits_), z);
    }
    return z;
  }
}
