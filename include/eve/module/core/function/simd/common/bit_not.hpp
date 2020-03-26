//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BIT_NOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BIT_NOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE auto bit_not_(EVE_SUPPORTS(cpu_)
                               , wide<T, N, ABI> const &v) noexcept
  {
    if constexpr( is_aggregated_v<ABI> )
    {
      return aggregate(bit_not, v);
    }
    else if constexpr( is_emulated_v<ABI>   )
    {
      return map(bit_not, v);
    }
    else return eve::bit_xor(v, Allbits(as(v)));
  }  
}

// -------------------------------------------------------------------------------------------------
// Infix operator support
namespace eve
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto operator~(wide<T, N, ABI> const &v) noexcept
  {
    return bit_not(v); 
  }
}

#endif
