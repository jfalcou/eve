//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <bit>

namespace eve::detail
{
  template<typename T, typename Target>
  EVE_FORCEINLINE constexpr Target bit_cast_impl(cpu_, T const &a, as<Target>) noexcept
  {
    // Fixes bad codegen on some compilers
    if constexpr(std::is_same_v<T, Target>)         return a;
    else if constexpr (sizeof(T) == sizeof(Target)) return std::bit_cast<Target>(a);
    // assume simd_value from there
    else if constexpr (T::size() == Target::size())
    {
      return Target{ [a](auto i) { return std::bit_cast<element_type_t<Target>>(a.get(i)); } };
    }
    else
    {
      const auto mem = reinterpret_cast<const element_type_t<Target>*>(&a.storage());
      return detail::apply<Target::size()>([&](auto... I) { return Target{ mem[I]... }; });
    }
  }
}

