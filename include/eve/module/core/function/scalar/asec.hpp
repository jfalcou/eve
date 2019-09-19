//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ASEC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ASEC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/acsc.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/constant.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/constant.hpp>
#include <eve/constant/nan.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T>
  EVE_FORCEINLINE constexpr auto asec_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept
  {
    if constexpr(std::is_same_v<T, double>)
    {
      if (is_equal(a0, One(as(a0)))) return Zero(as(a0));
      return Pio_2(as(a0)) +  (Constant<T, 0x3c91a62633145c07ll>()-acsc(a0));
    }
    else if constexpr(std::is_same_v<T, float>)
    {
      if (is_equal(a0, One(as(a0)))) return Zero(as(a0));
      return  Pio_2(as(a0))+(Constant<T,  0XB33BBD2EU>()-acsc(a0));
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::asec scalar ] - type is not an IEEEValue"); 
    }
  }

}

#endif
