//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_NEAREST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_NEAREST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/add.hpp>
#include <eve/function/sub.hpp>
#include <eve/constant/twotonmb.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto nearest_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &a0) noexcept
  {
    if constexpr(is_aggregated_v<ABI>)
      return aggregate(eve::nearest, a0);
    else if constexpr(is_emulated_v<ABI>)
      return map(eve::nearest, a0);
    else
    {
      if constexpr(std::is_floating_point_v<T>)
      {
        auto s   = bitofsign(a0);
        auto v   = bitwise_xor(a0, s);
        auto t2n = Twotonmb(as(a0));
        auto d0  = v + t2n;
        return bitwise_xor(if_else(is_less(v, t2n), d0 - t2n, v), s);
      }
      else if constexpr(std::is_integral_v<T>)
        return a0;
    }
  }
}

#endif
