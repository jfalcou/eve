//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ACOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ACOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/rec.hpp>
#include <eve/module/core/detail/simd/atan_kernel.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto acot_(EVE_SUPPORTS(cpu_)
                            , eve::wide<T,N,ABI> const &a) noexcept
  Requires( eve::wide<T,N,ABI>, floating_point<T>)
  {
    if constexpr( is_aggregated_v<ABI> )
    {
      return aggregate(eve::acot, a);
    }
    else if constexpr( is_emulated_v<ABI> )
    {
      return map(eve::acot, a);
    }
    else
    {
      auto x  = eve::abs(a);
      return bit_xor(atan_kernelw(rec(x), x), bitofsign(a));
    }
  }
}

#endif
