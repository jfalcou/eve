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
#include <eve/detail/implementation.hpp>
#include <eve/function/pedantic.hpp>

namespace eve::detail
{
  template<typename T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> min_( EVE_SUPPORTS(neon128_)
                                      , pedantic_type const &
                                      , wide<T, N, ABI> const &a0
                                      , wide<T, N, ABI> const &a1
                                      ) noexcept
  {
    auto tmp = eve::min(a0, a1);
    if constexpr(eve::platform::supports_invalids) tmp = if_else(is_nan(a1), a0, tmp);
    return if_else(is_eqz(a0) && is_eqz(a1), bit_or(a0, a1), tmp);
  }
}
