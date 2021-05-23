//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/constant/signmask.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/sqr.hpp>
#include <eve/module/real/math/detail/generic/cos_kernel.hpp>
#include <eve/module/real/math/detail/generic/sin_kernel.hpp>
#include <type_traits>
#include <utility>

namespace eve::detail
{
  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto
  sincos_finalize( wide<T, N, ABI> const & a0
                 , wide<T, N, ABI> const & fn
                 , wide<T, N, ABI> const & xr
                 , wide<T, N, ABI> const & dxr = wide<T, N, ABI>(0)) noexcept
  {
    using t_t = wide<T, N, ABI>;
    auto const tmp =  binarize(fn >= t_t(2));
    auto const swap_bit = (fma(t_t(-2), tmp, fn));
    auto const cos_sign_bit = binarize(is_nez(bit_xor(swap_bit, tmp)), signmask(eve::as<T>()));
    auto const sin_sign_bit = bit_xor(bitofsign(a0),if_else(tmp, signmask(eve::as<t_t>()), eve::zero));
    auto const z = eve::sqr(xr);
    auto const se = sin_eval(z, xr);
    auto const ce = cos_eval(z);
    auto const test = is_nez(swap_bit);

    return kumi::make_tuple ( bit_xor(if_else(test, ce, se), sin_sign_bit)
                            , bit_xor(if_else(test, se, ce), cos_sign_bit)
                            );
  }
}

