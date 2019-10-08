//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MANTISSA_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MANTISSA_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_nez.hpp> 
#include <eve/function/binarize.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/mantissabits.hpp>
#include <eve/constant/maxmantissa.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/platform.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto mantissa_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &a) noexcept
  {
    auto x = shr(mantissabits(a), Nbmantissabits<T>());
    auto test = is_nez(a);
    if constexpr(eve::platform::supports_infinites)
    {
      test = logical_or(test, is_not_finite(a));
    }
    return sub[test](x, Maxmantissa<T>());
  }
}

#endif
