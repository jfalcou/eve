//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_POW2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_POW2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_pow2_(EVE_SUPPORTS(cpu_)
                               , wide<T, N, ABI> const &x) noexcept
  requires(logical<wide<T, N, ABI>>, integral<T>)
  {
    return is_gtz(x) && is_eqz(bit_and(x, dec(x)));
  }
}

#endif
