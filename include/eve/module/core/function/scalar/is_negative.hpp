//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NEGATIVE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NEGATIVE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/false.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_negative_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      using si_t = eve::detail::as_integer_t<T, signed>;
      return bit_cast(is_ltz(bit_cast(a,as_<si_t>{})), as_<as_logical_t<T>>{});
    }
    else if constexpr(std::is_signed_v<T>)
    {
      return is_ltz(a);
    }
    else
    {
      return False(as(a));
    }
  }
}

#endif
