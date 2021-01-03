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

#include <eve/detail/implementation.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<integral_value T, integral_value U>
  EVE_FORCEINLINE  auto shr_(EVE_SUPPORTS(cpu_)
                            , T const &a0
                            , U const &a1) noexcept
  {
    if constexpr(scalar_value<T> && scalar_value<U>)
    {
      return static_cast<T>(a0 >> a1);
    }
    else if (has_emulated_abi_v<T> || has_emulated_abi_v<U>)
    {
      return map(eve::shr, a0, a1);
    }
    else if constexpr(has_aggregated_abi_v<T> || has_aggregated_abi_v<U>)
    {
      return aggregate(eve::shr, a0, a1);
    }
    else
    {
      return map(eve::shr, a0, a1);
    }
  }
}

namespace eve
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto operator >>(T const &v0, U const &v1) noexcept -> decltype(eve::shr(v0, v1))
  {
    return eve::shr(v0, v1);
  }

  // This is needed to prevent clang using an internal operator of comparison over simd vector
  // types with different value types, as some architectures are not
  // aware of the accurate element type in the storage
  template<real_simd_value T, real_simd_value U>
  EVE_FORCEINLINE  auto operator >> (T const &a
                                    , U const &b) noexcept
  requires different_value_type<T, U> = delete;
}
