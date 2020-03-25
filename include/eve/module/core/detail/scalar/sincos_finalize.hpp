//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_DETAIL_SCALAR_SINCOS_FINALIZE_HPP_INCLUDED
#define EVE_MODULE_CORE_DETAIL_SCALAR_SINCOS_FINALIZE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/detail/generic/cos_kernel.hpp>
#include <eve/module/core/detail/generic/sin_kernel.hpp>   
#include <eve/function/shl.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/is_negative.hpp>
#include <type_traits>
#include <utility>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto sincos_finalize( T a0, T fn, T xr, T dxr = T(0)) noexcept
  Requires(std::tuple<T, T>, Vectorizable<T>)
  {
    T z = sqr(xr);
    T  se0 = sin_eval(z, xr);
    T  ce0 = cos_eval(z);
    using i_t =  detail::as_integer_t<T, signed>; 
    i_t n = toint(fn);
    i_t swap_bit = n&One<i_t>();
    T  sin_sign_bit = bit_xor(bitofsign(a0), shl(n&i_t(2), sizeof(i_t)*8-2));
    i_t cos_sign_bit = shl(bit_xor(swap_bit, (n&i_t(2))>>1), sizeof(i_t)*8-1);
    ce0 = fnma(se0, dxr, ce0);
    se0 = fma(dxr, ce0, se0);
    if (swap_bit) std::swap(ce0, se0); 
    T se = bit_xor(se0,sin_sign_bit);   
    T ce = bit_xor(ce0,cos_sign_bit);
    return  std::tuple<T, T>{se, ce};
  }
}

#endif
