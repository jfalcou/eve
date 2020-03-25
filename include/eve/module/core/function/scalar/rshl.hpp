//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_RSHL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_RSHL_HPP_INCLUDED

#include <eve/assert.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/shl.hpp>
#include <eve/assert.hpp>
#include <type_traits>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  rshl_(EVE_SUPPORTS(cpu_), T const &a0, U const &a1) noexcept Requires(T, integral<U>, integral<T>)
  {
    if constexpr(std::is_signed_v<U>) { return (a1 > 0) ? shl(a0, a1) : shr(a0, -a1); }
    else
    {
      return shl(a0, a1);
    }
  }
}

#endif
