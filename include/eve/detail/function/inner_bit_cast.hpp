//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/function/bit_cast.hpp>

namespace eve::detail
{
  // allows bit-casts between emulated and non-emulated types
  template<value Src, value Tgt>
  constexpr EVE_FORCEINLINE Tgt inner_bit_cast(Src src, as<Tgt> tgt)
    requires (sizeof(element_type_t<Src>) * cardinal_v<Src> == sizeof(element_type_t<Tgt>) * cardinal_v<Tgt>)
  {
    if constexpr (sizeof(Src) == sizeof(Tgt))
    {
      return bit_cast_impl(current_api, src, tgt);
    }
    else if constexpr (Src::size() == Tgt::size())
    {
      return Tgt{ [&](auto i, auto) { return bit_cast_impl(current_api, src.get(i), as_element<Tgt>{}); } };
    }
    else
    {
      const auto mem = reinterpret_cast<const element_type_t<Tgt>*>(&src.storage());
      return detail::apply<Tgt::size()>([&](auto... I) { return Tgt{ mem[I]... }; });
    }
  }
}
