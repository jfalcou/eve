//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_REM_PIO2_CEPHES_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_REM_PIO2_CEPHES_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/quadrant.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/trunc.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/twoopi.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE auto  rem_pio2_cephes_(EVE_SUPPORTS(cpu_)
                                         , T const &x) noexcept
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      auto pio2_1 = Ieee_constant<T, 0X3FC90F80, 0X3FF921FB54400000LL>();
      auto pio2_2 = Ieee_constant<T, 0X37354400, 0X3DD0B4611A600000LL>();
      auto pio2_3 = Ieee_constant<T, 0X2E85A300, 0X3BA3198A2E000000LL>();
      T n =  eve::nearest(x*Twoopi<T>());
      T xr = fnma(n, pio2_1, x);
      xr   = fnma(n, pio2_2, xr);
      xr   = fnma(n, pio2_3, xr);
      return std::make_tuple(quadrant(n), xr, T(0)); 
    }
    else
    {
      static_assert(std::is_floating_point_v<value_type_t<T>>, "rem_pio2_cephes paramete is not IEEEValue"); 
      return std::make_tuple(T{},T{},T{}); 
    }
  }
}

#endif
