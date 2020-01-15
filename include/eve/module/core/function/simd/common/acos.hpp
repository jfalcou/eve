//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ACOS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ACOS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/div.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto acos_(EVE_SUPPORTS(cpu_)
                           ,  raw_type const & 
                            , eve::wide<T,N,ABI> const &a0) noexcept
  requires( eve::wide<T,N,ABI>, floating_point<T>)
  {
    if constexpr( is_aggregated_v<ABI> )
    {
      return aggregate(eve::raw_(eve::acos), a0);
    }
    else if constexpr( is_emulated_v<ABI>   )
    {
      return map(eve::raw_(eve::acos), a0);
    }
    else
    {
      using t_t = eve::wide<T,N,ABI>;
      // small correction with pio_2lo
      return if_else(a0 == One(as(a0)), eve::zero_,
                     Pio_2(as(a0)) +  (Ieee_constant<t_t, 0XB33BBD2EU, 0x3c91a62633145c07ll>()-asin(a0)));

    }
  }

  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto acos_(EVE_SUPPORTS(cpu_)
                            , eve::wide<T,N,ABI> const &a0) noexcept
  requires( eve::wide<T,N,ABI>, floating_point<T>)
  {
    if constexpr( is_aggregated_v<ABI> )
    {
      return aggregate(eve::acos, a0);
    }
    else if constexpr( is_emulated_v<ABI>   )
    {
      return map(eve::acos, a0);
    }
    else if constexpr( std::is_floating_point_v<T> )
    {
      auto x = eve::abs(a0);
      auto x_larger_05 = is_greater(x, eve::Half(as(a0)));
      // for T same as float
      // 2130706432 values computed.
      // 1968272987 values (92.38%) within 0.0 ULPs
      //  162433445 values (7.62%)  within 0.5 ULPs
      // 8.5 cycles/element SSE4.2 g++-4.8
      x  = if_else(x_larger_05, eve::sqrt(fma(eve::Mhalf(as(a0)), x, eve::Half(as(a0)))), a0);
      x  = asin(x);
      x =  add[x_larger_05](x, x);
      x  = eve::if_else(is_less(a0, eve::Mhalf(as(a0))), eve::Pi(as(a0))-x, x);
      return eve::if_else(x_larger_05, x, eve::Pio_2(as(a0))-x);
    }
  }
}

#endif
