//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_ODD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_ODD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/function/is_even.hpp>
#include <eve/function/dec.hpp>
#include <eve/constant/one.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  is_odd_(EVE_SUPPORTS(cpu_), T const &a) noexcept requires(as_logical_t<T>, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      auto da = dec(a);     
      return (a!= da) && is_even(da);
    }
    else
      return (a & One(as(a)));
  }
}

#endif
