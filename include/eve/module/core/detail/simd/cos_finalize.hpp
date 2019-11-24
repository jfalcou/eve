//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_DETAIL_SIMD_COS_FINALIZE_HPP_INCLUDED
#define EVE_MODULE_CORE_DETAIL_SIMD_COS_FINALIZE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/detail/generic/sin_kernel.hpp>
#include <eve/module/core/detail/generic/cos_kernel.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/mhalf.hpp>
#include <type_traits>


namespace eve::detail
{
  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE constexpr wide<T, N, ABI>
  cos_finalize( wide<T, N, ABI> const & fn
              , wide<T, N, ABI> const & xr
              , wide<T, N, ABI> const & dxr = wide<T, N, ABI>(0)) noexcept
  {
    using t_t = wide<T, N, ABI>; 
    auto tmp =  binarize(fn >= t_t(2));
    auto swap_bit = (fma(t_t(-2), tmp, fn));
    auto sign_bit = binarize(is_nez(bitwise_xor(swap_bit, tmp)), Signmask<T>()); 
    t_t z = sqr(xr);
    t_t se = sin_eval(z, xr);
    t_t ce = cos_eval(z);
    t_t z1 = if_else(swap_bit, fma(dxr, ce, se), fnma(se, dxr, ce));
    return bitwise_xor(z1, sign_bit); 
  }
}

#endif
