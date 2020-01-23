//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2019 Joel FALCOU
   Copyright 2019 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ATANH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ATANH_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>   
#include <eve/function/bit_xor.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/log1p.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/constant/half.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto atanh_(EVE_SUPPORTS(cpu_)
                                       , T x) noexcept
  requires(T, floating_point<T>)
  {
      T absx = eve::abs(x);
      T t =  absx+absx;
      T z1 = oneminus(absx);
      return bit_xor(bitofsign(x),
                         Half<T>()*log1p((absx < Half<T>())
                                          ? fma(t, absx/z1, t)
                                          : t/z1)
                        );   
  }
}

#endif
