//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ASEC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ASEC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/div.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp> 
#include <eve/constant/pio_2.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto asec_(EVE_SUPPORTS(cpu_)
                            , eve::wide<T,N,ABI> const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      using t_t = wide<T,N,ABI>;
      if constexpr( is_aggregated_v<ABI> )
        return aggregate(eve::asec, a0);
      else if constexpr( is_emulated_v<ABI>   )
        return map(eve::asec, a0);
      else if constexpr( std::is_same_v<T, double> )
      {
        auto tmp =  (Pio_2(as(a0))-acsc(a0)) +  Constant<t_t, 0x3c91a62633145c07ll>();
        return if_else(is_equal(a0, One(as(a0))), eve::zero_, tmp);

      }   
      else if constexpr( std::is_same_v<T, float> )
      {
        auto tmp =  (eve::Pio_2(as(a0))-eve::acsc(a0)) + Constant<t_t,  0XB33BBD2EU>(); 
        return if_else(is_equal(a0, One(as(a0))), eve::zero_ ,tmp);

      }
      else
      {
        EVE_ASSERT(std::is_floating_point_v<T>, "[eve::asec simd] - type is not an IEEEValue"); 
      }
    }
  }

}

#endif
