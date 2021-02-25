//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/real/math/detail/generic/tancot_kernel.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/eps.hpp>
#include <type_traits>



namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE constexpr wide<T, N, ABI> tan_finalize( wide<T, N, ABI> const & a0
                                                        , wide<T, N, ABI> const & n
                                                        , wide<T, N, ABI> const & xr
                                                        , wide<T, N, ABI> const & dxr = wide<T, N, ABI>(0)) noexcept
  {
    using t_t = wide<T, N, ABI>;
    auto tmp = binarize( n >= t_t(2));
    auto swap_bit = (fma(t_t(-2), tmp, n));
    auto test = is_eqz(swap_bit);
    t_t y = tancot_eval(xr);
    y = if_else(test,y,-rec(y));
    y = fma(dxr, fma(y, y, one(eve::as<T>())), y);
    return if_else(abs(a0) < Eps<t_t>(), a0, bit_xor(y, bitofsign(a0)));
  }
}

