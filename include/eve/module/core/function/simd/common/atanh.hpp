//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2019 Joel FALCOU
   Copyright 2019 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_ATANH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_ATANH_HPP_INCLUDED
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/add.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/div.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/log1p.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/constant/half.hpp>
#include <type_traits>
#include <tuple>


namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE auto atanh_(EVE_SUPPORTS(cpu_)
                            , const T &x) noexcept
  requires(T, vectorized<T>, behave_as<floating_point, T>)
  {
    T absx = eve::abs(x);
    T t =  absx+absx;
    T z1 = oneminus(absx);
    auto test =  is_less(absx, Half<T>());
    T tmp = if_else(test, absx, t)/z1;
    return bit_xor(bitofsign(x), Half<T>()*log1p(if_else(test, fma(t,tmp,t), tmp)));
  }
}

#endif

