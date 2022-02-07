//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/nan.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/bit_and.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N> max_( EVE_SUPPORTS(neon128_)
                                      , pedantic_type const &
                                      , wide<T, N> const &a0
                                      , wide<T, N> const &a1
                                      ) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    auto tmp = eve::max(a0, a1);
    if constexpr(eve::platform::supports_invalids) tmp = if_else(is_nan(a1), a0, tmp);
    return if_else(is_eqz(a0) && is_eqz(a1), bit_and(a0, a1), tmp);
  }
}
