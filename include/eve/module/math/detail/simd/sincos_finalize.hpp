//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi>
#include <eve/module/core.hpp>
#include <eve/module/math/detail/generic/cos_kernel.hpp>
#include <eve/module/math/detail/generic/sin_kernel.hpp>

namespace eve::detail
{
template<typename T, typename N>
EVE_FORCEINLINE auto
sincos_finalize(wide<T, N> const& a0,
                wide<T, N> const& fn,
                wide<T, N> const& xr,
                wide<T, N> const& dxr = wide<T, N>(0)) noexcept
{
  using t_t               = wide<T, N>;
  auto const tmp          = binarize(fn >= t_t(2));
  auto const swap_bit     = (fma(t_t(-2), tmp, fn));
  auto const cos_sign_bit = binarize(is_nez(bit_xor(swap_bit, tmp)), signmask(eve::as<T>()));
  auto const sin_sign_bit =
      bit_xor(bitofsign(a0), if_else(tmp, signmask(eve::as<t_t>()), eve::zero));
  auto const z    = eve::sqr(xr);
  auto const se   = sin_eval(z, xr);
  auto const ce   = cos_eval(z);
  auto const test = is_nez(swap_bit);

  return kumi::make_tuple(bit_xor(if_else(test, ce, se), sin_sign_bit),
                          bit_xor(if_else(test, se, ce), cos_sign_bit));
}
}
