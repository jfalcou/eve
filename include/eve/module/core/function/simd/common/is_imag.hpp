//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_IMAG_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_IMAG_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/logical_not.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_imag_(EVE_SUPPORTS(cpu_)
                               , wide<T, N, ABI> const &v) noexcept
  {
      return is_eqz(v);
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_imag_(EVE_SUPPORTS(cpu_)
                               , logical<wide<T, N, ABI>> const &v) noexcept
  {
    return logical_not(v);
  }
}

#endif
