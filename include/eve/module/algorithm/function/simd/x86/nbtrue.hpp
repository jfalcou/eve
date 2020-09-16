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
#include <eve/detail/category.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  //================================================================================================
  // X86 implementation
  //================================================================================================
  template<real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto nbtrue_(EVE_SUPPORTS(sse2_), logical<wide<T, N, ABI>> const &v) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

    if constexpr(cat == category::int16x8 || cat == category::uint16x8)
    {
      // Using bitmap directly on short is pessimistic, we do a custom check here
      using type  = logical<wide<T, N, ABI>>;
      using tgt   = typename type::template rebind<std::uint8_t,typename N::combined_type>;
      return bit_cast(v,as_<tgt>()).bitmap().count() / 2;
    }
    else
    {
      return v.bitmap().count();
    }
  }
}
