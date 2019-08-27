//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_RSQRT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_RSQRT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE wide<T, N, ABI> rsqrt_( EVE_SUPPORTS(cpu_),
                                          wide<T, N, ABI> const & a0
                                        ) noexcept
  {
    if constexpr( is_aggregated_v<ABI> ) return aggregate(eve::rsqrt, a0);
    else return map(rsqrt, a0);
  }

  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE wide<T, N, ABI> rsqrt_( EVE_SUPPORTS(cpu_),
                                          raw_type const &,
                                          wide<T, N, ABI> const & a0
                                        ) noexcept
  {
    return eve::rsqrt(a0);
  }
}

#endif
