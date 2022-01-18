//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>
#include <eve/module/math/detail/generic/tancot_kernel.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE constexpr wide<T, N> cot_finalize( wide<T, N> const & a0
                                                        , wide<T, N> const & n
                                                        , wide<T, N> const & xr
                                                        , wide<T, N> const & dxr) noexcept
  {
    using t_t = wide<T, N>;
    auto tmp = binarize( n >= t_t(2));
    auto swap_bit = (fma(t_t(-2), tmp, n));
    auto test = is_eqz(swap_bit);
    t_t y = tancot_eval(xr);
    y = if_else(test,rec(y),-y);
    y = fma(dxr, fma(y, y, one(eve::as<T>())), y);
    return if_else(abs(a0) < eps(as<t_t>()), pedantic(rec)(a0), bit_xor(y, bitofsign(a0)));
  }
}
