//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_NBTRUE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_NBTRUE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/extract.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/binarize.hpp>
#include <eve/logical.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE size_t nbtrue_(EVE_SUPPORTS(cpu_)
                           , logical<wide<T, N, ABI>> const &v) noexcept
  {
    if constexpr(is_aggregated_v<ABI>)
    {
      auto [ sl, sh] = v.slice();
      return nbtrue(sl) + nbtrue(sh);
    }
    else
    {
      auto iv = binarize(v);
      std::size_t r = 0;
      for(int i=0; i < N::value; ++i) r += iv[i];
      return r;
    }
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE size_t nbtrue_(EVE_SUPPORTS(cpu_)
                           , wide<T, N, ABI> const &v) noexcept
  {
    return nbtrue(is_nez(v));
  }
}

#endif
