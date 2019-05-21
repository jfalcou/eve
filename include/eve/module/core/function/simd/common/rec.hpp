//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_REC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_REC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/tags.hpp>
#include <eve/forward.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/one.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_equal.hpp>
#include <type_traits>
#include <cassert>

namespace eve::detail
{

  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto rec_(EVE_SUPPORTS(simd_),
                            wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(is_aggregated_v<ABI>)
      return aggregate(eve::rec, v);
    else if  constexpr(is_emulated_v<ABI>)
      return map(eve::rec, v);
    else
    {
      if constexpr(std::is_floating_point_v<T>)
        return map(rec, v);
      else
      {
       if constexpr(std::is_unsigned_v<T>)
        return if_else(v, if_else(v == One(as(v)), One(as(v)), Zero(as(v))), Allbits(as(v)));
       else
         return if_else(v, if_else(eve::abs(v) == One(as(v)), v, Zero(as(v))), Valmax(as(v)));
      }
    }
  }
  
}

#endif
