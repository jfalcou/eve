//================================================================================================== 
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SHR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/function/scalar/bitwise_cast.hpp>
#include <type_traits>
#include <cassert>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto shr_(EVE_SUPPORTS(cpu_), T const &a0, std::ptrdiff_t a1) noexcept
  {
    assert(detail::assert_good_shift<T>(a1) && "shr: a shift is out of range");
    if constexpr(std::is_floating_point_v<T>)
    {
      using i_t = as_integer_t<T, signed>;
      return bitwise_cast<T>(shr(eve::bitwise_cast<i_t>(a0), a1));
    }
    else 
    {
      return T(a0 >>  a1);
    }
  }
}

#endif
