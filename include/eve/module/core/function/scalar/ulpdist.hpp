//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ULPDIST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ULPDIST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>
#include <eve/function/abs.hpp>
#include <eve/function/dist.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/max.hpp>
#include <eve/function/min.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/zero.hpp>
#include <eve/concept/vectorizable.hpp>

namespace eve::detail
{

  template<typename T>
  EVE_FORCEINLINE constexpr auto
  ulpdist_(EVE_SUPPORTS(cpu_)
          , T const &a0
          , T const &a1) noexcept
  requires(T, vectorizable<T>)
  {
    if(numeric_(is_equal)(a0, a1)) return Zero<T>(); 
    if constexpr(std::is_floating_point_v<T>)
    {
       using i_t = as_integer_t<T>;
        auto [m1, e1] = pedantic_(ifrexp)(a0);
        auto [m2, e2] = pedantic_(ifrexp)(a1);
        i_t expo =-eve::max(e1, e2);
        return  (eve::is_equal(e1, e2)
                 ? eve::abs(m1-m2)
                 : eve::abs( eve::pedantic_(ldexp)(a0, expo)
                             - eve::pedantic_(ldexp)(a1, expo)))/Eps<T>(); 
    } 
    else return dist(a0, a1);
  }
}

#endif
