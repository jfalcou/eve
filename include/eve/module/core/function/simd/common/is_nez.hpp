//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NEZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NEZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_not_equal.hpp>
#include <eve/constant/zero.hpp>
#include <eve/forward.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_nez_(EVE_SUPPORTS(simd_),wide<T, N, ABI> const &v) noexcept
  {
    if constexpr( is_native_v<ABI> )
    {
      return is_not_equal(v, Zero(as(v)));
    }
    else
    {
      if constexpr( is_aggregated_v<ABI>) return aggregate(eve::is_nez, v);
      if constexpr( is_emulated_v<ABI>  ) return map(eve::is_nez, v);
    }
  }
}

#endif
