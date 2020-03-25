//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_DETAIL_SCALAR_COS_FINALIZE_HPP_INCLUDED
#define EVE_MODULE_CORE_DETAIL_SCALAR_COS_FINALIZE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/detail/generic/sin_kernel.hpp>
#include <eve/module/core/detail/generic/cos_kernel.hpp>   
#include <eve/function/shl.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <type_traits>


namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto cos_finalize( T fn, T xr, T dxr = T(0)) noexcept
  Requires(T, Vectorizable<T>)
  {
     using i_t =  detail::as_integer_t<T, signed>; 
     i_t n = i_t(fn);
     i_t swap_bit = n&i_t(1);
     i_t sign_bit = shl(bit_xor(swap_bit, (n&i_t(2))>>1), sizeof(i_t)*8-1);
     T z = sqr(xr);
     T  se = sin_eval(z, xr);
     T  ce = cos_eval(z);
     z =  swap_bit ?  fma(dxr, ce, se) : fnma(se, dxr, ce); 
     return bit_xor(z,sign_bit); 
  }
}

#endif
