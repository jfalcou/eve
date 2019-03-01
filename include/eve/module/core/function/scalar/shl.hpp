//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SHL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SHL_HPP_INCLUDED

#include <eve/assert.hpp>
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
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto shl_(EVE_SUPPORTS(cpu_), T const &a0, U const &a1) noexcept
  requires(T, Integral<U>)
  {
    EVE_ASSERT( detail::assert_good_shift<T>(a1)
              , " At least one of " << a1 << "elements is out of the range [0, " << sizeof(T)*8 << "[."
              );

    if constexpr(std::is_floating_point_v<T>)
    {
      using i_t = as_integer_t<T, signed>;
      return bitwise_cast<T>(shl(eve::bitwise_cast<i_t>(a0), a1));
    }
    else
    {
      return T(a0 << a1);
    }
  }
}

#endif
