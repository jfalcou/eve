//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_EXPONENT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_EXPONENT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_nez.hpp> 
#include <eve/function/binarize.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/exponentbits.hpp>
#include <eve/constant/maxexponent.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/platform.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto exponent_(EVE_SUPPORTS(cpu_)
                                , wide<T, N, ABI> const &a) noexcept
  requires(as_integer_t<wide<T, N, ABI>>, floating_point<T>)
  {
    auto x = shr(exponentbits(a), Nbmantissabits<T>());
    //   auto test = is_nez(a);
    return if_else(is_not_finite(a), eve::zero_, sub[is_nez(a)](x, Maxexponent<T>())); 

  }
}

#endif
