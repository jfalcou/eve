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

#include <eve/constant/signmask.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/sqr.hpp>
#include <eve/module/math/detail/generic/cos_kernel.hpp>
#include <eve/module/math/detail/generic/sin_kernel.hpp>

#include <type_traits>
#include <utility>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE std::tuple<wide<T, N, ABI>, wide<T, N, ABI>>
                  sincos_finalize(wide<T, N, ABI> const &a0,
                                  wide<T, N, ABI> const &fn,
                                  wide<T, N, ABI> const &xr,
                                  wide<T, N, ABI> const &dxr = wide<T, N, ABI>(0)) noexcept
  {
    using t_t         = wide<T, N, ABI>;
    auto tmp          = binarize(fn >= t_t(2));
    auto swap_bit     = (fma(t_t(-2), tmp, fn));
    auto cos_sign_bit = binarize(is_nez(bit_xor(swap_bit, tmp)), signmask(eve::as<T>()));
    auto sin_sign_bit = bit_xor(bitofsign(a0), if_else(tmp, signmask(eve::as<t_t>()), eve::zero));
    auto z            = eve::sqr(xr);
    auto se           = sin_eval(z, xr);
    auto ce           = cos_eval(z);
    auto test         = is_nez(swap_bit);
    return std::make_tuple(bit_xor(if_else(test, ce, se), sin_sign_bit),
                           bit_xor(if_else(test, se, ce), cos_sign_bit));
  }
}
