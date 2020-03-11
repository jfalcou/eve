//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_DETAIL_SCALAR_TAN_FINALIZE_HPP_INCLUDED
#define EVE_MODULE_CORE_DETAIL_SCALAR_TAN_FINALIZE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/detail/generic/tancot_kernel.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/eps.hpp>
#include <type_traits>


namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto tan_finalize(T a0,  T fn, T xr, T dxr = T(0)) noexcept
  requires(T, vectorizable<T>)
  {
    if (eve::abs(a0) < Eps<T>()) return a0; 
    if (is_not_finite(xr)) return Nan<T>();
    if (is_eqz(a0)) return a0;
    T y = tancot_eval(xr);
    y =  (int(fn)&1) ? -rec(y): y;
    if (dxr) y+= dxr*fma(y, y, One<T>()); 
    return bit_xor(y, bitofsign(a0));
  }
}

#endif
