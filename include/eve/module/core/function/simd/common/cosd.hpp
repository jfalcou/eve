//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_COSD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_COSD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/module/core/detail/generic/cos_kernel.hpp>
#include <eve/function/deginrad.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/trigo_tags.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE constexpr auto cosd_(EVE_SUPPORTS(cpu_)
                                     , restricted_type const &
                                     , wide<T, N, ABI>a0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      auto x2 = sqr(deginrad(a0)); 
      return if_else(is_not_less_equal(x2, T(45*45)), eve::allbits_, cos_eval(x2));
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cosd simd ] - type is not an IEEEValue"); 
    }   
  }
}

#endif
