//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_DETAIL_GENERIC_COS_FINALIZE_HPP_INCLUDED
#define EVE_MODULE_CORE_DETAIL_GENERIC_COS_FINALIZE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
// #include <eve/module/core/detail/generic/sin_kernel.hpp>
// #include <eve/module/core/detail/generic/cos_kernel.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/constant/mhalf.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>


namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cos_eval( T const &  z) noexcept
  {
    using elt_t = element_type_t<T>; 
    if constexpr(std::is_same_v<elt_t, float>)
    {
      T y = horn<T, 0x3d2aaaa5 , 0xbab60619 , 0x37ccf5ce> (z);
      return inc( fma(z,Mhalf<T>(), y* sqr(z)));
    }
    else if constexpr(std::is_same_v<elt_t, double>)
    {
      T y = horn<T, 0x3fe0000000000000ll, 0xbfa5555555555551ll, 0x3f56c16c16c15d47ll,
        0xbefa01a019ddbcd9ll, 0x3e927e4f8e06d9a5ll, 0xbe21eea7c1e514d4ll, 0x3da8ff831ad9b219ll > (z);
      return oneminus(y*z);
    }
  }
  
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sin_eval( const T & z
                                         , const T & x) noexcept
  {
    // here T is float or double and x positive
    using elt_t = element_type_t<T>; 
   if constexpr(std::is_same_v<elt_t, float>)
    {
      T  y1 = horn<T, 0xbe2aaaa2 , 0x3c08839d , 0xb94ca1f9> (z);
      return fma(y1*z,x,x);
    }
    else if constexpr(std::is_same_v<elt_t, double>)
    {
      T y1 = horn<T, 0xbfc5555555555548ll, 0x3f8111111110f7d0ll, 0xbf2a01a019bfdf03ll,
        0x3ec71de3567d4896ll, 0xbe5ae5e5a9291691ll, 0x3de5d8fd1fcf0ec1ll> (z);
      return fma(y1*z,x,x);  
    }
  }
  
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cos_finalize(  const T & fn
                                             ,  const T & xr
                                             ,  const T & dxr = T(0)) noexcept
  {
    if constexpr(scalar_value<T>)
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
    else
    {
      using elt_t =  element_type_t<T>; 
      auto tmp =  binarize(fn >= T(2));
      auto swap_bit = (fma(T(-2), tmp, fn));
      auto sign_bit = binarize(is_nez(bit_xor(swap_bit, tmp)), Signmask<elt_t>()); 
      T z = sqr(xr);
      T se = sin_eval(z, xr);
      T ce = cos_eval(z);
      z = if_else(swap_bit, fma(dxr, ce, se), fnma(se, dxr, ce));
      return bit_xor(z, sign_bit); 
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sin_finalize(  const T & sbit
                                             ,  const T & fn
                                             ,  const T & xr
                                             ,  const T & dxr = T(0)) noexcept
  {
    if constexpr(scalar_value<T>)
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
    else
    {
      auto tmp =  binarize(fn >= T(2));     
      auto swap_bit = (fma(T(-2), tmp, fn));
      auto sign_bit = bit_xor(sbit, if_else(tmp, Signmask<T>(), eve::zero_));
      T z = sqr(xr);
      T se = sin_eval(z, xr);
      T ce = cos_eval(z);
      T z1 = if_else(swap_bit, fnma(se, dxr, ce), fma(dxr, ce, se));
      return bit_xor(z1, sign_bit); 
    }
  }

  
}

#endif

