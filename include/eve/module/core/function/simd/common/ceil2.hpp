//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_CEIL2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_CEIL2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/all.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/exp2.hpp>
#include <eve/function/floor2.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/bit_shr.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto ceil2_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(is_aggregated_v<ABI>) { return aggregate(eve::ceil2, v); }
    else if constexpr(is_emulated_v<ABI>)
    {
      return map(eve::ceil2, v);
    }
    else if constexpr(is_native_v<ABI>)
    {
      auto tmp =  floor2(v);
      return if_else(is_less_equal(v, One(as(v)))
                    , One(as(v))
                    , if_else(is_less(tmp, v), tmp*2,  tmp)); 
    }
  }
}

#endif
