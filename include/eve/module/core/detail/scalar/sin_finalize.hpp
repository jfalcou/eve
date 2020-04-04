//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_DETAIL_SCALAR_SIN_FINALIZE_HPP_INCLUDED
#define EVE_MODULE_CORE_DETAIL_SCALAR_SIN_FINALIZE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/detail/generic/sin_kernel.hpp>
#include <eve/module/core/detail/generic/cos_kernel.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/nan.hpp>
#include <type_traits>


namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto sin_finalize(T sbit,  T fn, T xr, T dxr = T(0)) noexcept
  Requires(T, Vectorizable<T>)
  {
    using i_t =  detail::as_integer_t<T, signed>; 
    if (is_not_finite(xr)) return Nan<T>();
    i_t n = toint(fn);
    i_t swap_bit = n&One<i_t>();
    T  sign_bit = bit_xor(sbit, shl(n&i_t(2), sizeof(i_t)*8-2));
    T z = sqr(xr);
    T  se = sin_eval(z, xr);
    T  ce = cos_eval(z);
    xr =  swap_bit ? fnma(se, dxr, ce) : fma(dxr, ce, se);
    return bit_xor(xr,sign_bit);
  }
}

#endif
