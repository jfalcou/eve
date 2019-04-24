//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NGEZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NGEZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/is_not_equal.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/false.hpp>
#include <eve/as_logical.hpp>
#include <eve/is_logical.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE auto is_ngez_(EVE_SUPPORTS(simd_), T const &v) noexcept
                            requires( as_logical_t<T>, Vectorized<T> )
  {
    if constexpr(std::is_unsigned_v<T> || is_logical_v<T>)
      return False(as(v));
    else
    {
      if constexpr(std::is_floating_point_v<T>)
        return is_not_greater_equal(v, Zero(as(v)));
      else 
        return is_ltz(v); 
    }   
  }
}

#endif
