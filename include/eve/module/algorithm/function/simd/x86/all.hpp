//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <concepts>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  //================================================================================================
  // X86 implementation
  //================================================================================================
  template<real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(sse2_), logical<wide<T, N, ABI>> const &v) noexcept
  {
    if constexpr( N::value == 1)
    {
      return v[0];
    }
    else if constexpr(sizeof(T) == 2)
    {
      using tgt = typename logical<wide<T, N, ABI>>::template rebind< std::uint8_t
                                                                    , typename N::combined_type
                                                                    >;
      return bit_cast(v, as_<tgt>()).bitmap().all();
    }
    else
    {
      return v.bitmap().all();
    }
  }
}
