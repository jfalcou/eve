//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_REM_PIO2_MEDIUM_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_REM_PIO2_MEDIUM_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/quadrant.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/trunc.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/twoopi.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE auto  rem_pio2_medium_(EVE_SUPPORTS(cpu_)
                                         , T const &x) noexcept
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      // ok for |x| <= 2^19*(pi/2), double 2^7*(pi/2) float medium_ size */
      auto pio2_1 = Ieee_constant<T, 0X3FC90F80, 0X3FF921FB54400000LL>();
      auto pio2_2 = Ieee_constant<T, 0X37354400, 0X3DD0B4611A600000LL>();
      auto pio2_3 = Ieee_constant<T, 0X2E85A300, 0X3BA3198A2E000000LL>();
      auto pio2_1t = Ieee_constant<T, 0X37354443, 0X3DD0B4611A626331LL>();
      auto pio2_2t = Ieee_constant<T, 0X2E85A308, 0X3BA3198A2E037073LL>();
      auto pio2_3t = Ieee_constant<T, 0X248D3132, 0X397B839A252049C1LL>();
      T fn  =  eve::nearest(x*Twoopi<T>());
      T r  = x-fn*pio2_1;
      T w  = fn*pio2_1t;
      T t2 = r;
      w  = fn*pio2_2;
      r  = t2-w;
      w  = fn*pio2_2t-((t2-r)-w);
      t2 = r;
      w  = fn*pio2_3;
      r  = t2-w;
      w  = fn*pio2_3t-((t2-r)-w);
      T xr = r-w;
      return std::tuple<T, T>{quadrant(fn), xr};
    }
    else
    {
      static_assert(std::is_floating_point_v<value_type_t<T>>, "rem_pio2_cephes parameter is not IEEEValue");
      return T{}; 
    }
  }

  template<typename T>
  EVE_FORCEINLINE auto  rem_pio2_medium_(EVE_SUPPORTS(cpu_)
                                        , pedantic_type const &
                                        , T const &x) noexcept
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      // ok for |x| <= 2^19*(pi/2), medium_ size */
      //      * pio2_1:   first  33 bit of pi/2
      //      * pio2_1t:  pi/2 - pio2_1
      //      * pio2_2:   second 33 bit of pi/2
      //      * pio2_2t:  pi/2 - (pio2_1+pio2_2)
      //      * pio2_3:   third  33 bit of pi/2
      //      * pio2_3t:  pi/2 - (pio2_1+pio2_2+pio2_3)
      auto pio2_1 = Ieee_constant<T, 0X3FC90F80, 0X3FF921FB54400000LL>();
      auto pio2_2 = Ieee_constant<T, 0X37354400, 0X3DD0B4611A600000LL>();
      auto pio2_3 = Ieee_constant<T, 0X2E85A300, 0X3BA3198A2E000000LL>();
      auto pio2_1t = Ieee_constant<T, 0X37354443, 0X3DD0B4611A626331LL>();
      auto pio2_2t = Ieee_constant<T, 0X2E85A308, 0X3BA3198A2E037073LL>();
      auto pio2_3t = Ieee_constant<T, 0X248D3132, 0X397B839A252049C1LL>();
      T fn  =  eve::nearest(x*Twoopi<T>());
      T r  = x-fn*pio2_1;
      T w  = fn*pio2_1t;
      T t2 = r;
      w  = fn*pio2_2;
      r  = t2-w;
      w  = fn*pio2_2t-((t2-r)-w);
      t2 = r;
      w  = fn*pio2_3;
      r  = t2-w;
      w  = fn*pio2_3t-((t2-r)-w);
      T xr = r-w;
      T xrc = (r-xr)-w;
      return std::tuple<T, T, T>{quadrant(fn), xr, xrc};
    }
    else
    {
      static_assert(std::is_floating_point_v<value_type_t<T>>, "pedantic(rem_pio2_cephes) parameter is not IEEEValue");
      return T{}; 
    }
  } 
}

#endif
