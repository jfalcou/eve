//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/detail/generic/tancot_kernel.hpp>

namespace eve::detail
{
template<typename T, typename N>
EVE_FORCEINLINE constexpr wide<T, N>
tan_finalize(wide<T, N> const& a0,
             wide<T, N> const& n,
             wide<T, N> const& xr,
             wide<T, N> const& dxr = wide<T, N>(0)) noexcept
{
  using t_t     = wide<T, N>;
  auto tmp      = binarize(n >= t_t(2));
  auto swap_bit = (fma(t_t(-2), tmp, n));
  auto test     = is_eqz(swap_bit);
  t_t  y        = tancot_eval(xr);
  y             = if_else(test, y, -rec(y));
  y             = fma(dxr, fma(y, y, one(eve::as<T>())), y);
  return if_else(abs(a0) < Eps<t_t>(), a0, bit_xor(y, bitofsign(a0)));
}
}
