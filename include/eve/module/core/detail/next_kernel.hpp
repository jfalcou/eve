//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/constant/signmask.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/sub.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr as_integer_t<T>
  bitinteger(T const& a) noexcept
  {
    using r_t = as_integer_t<T>;
    r_t a0    = bit_cast(a, as<r_t>());
    return sub[if_(is_ltz(a0)).else_(a0)](signmask(eve::as<r_t>()),a0);
  }

  template<typename T>
  EVE_FORCEINLINE constexpr as_floating_point_t<T>
  bitfloating(T const& a) noexcept
  {
    using r_t = as_floating_point_t<T>;
    T s       = bit_cast(signmask(eve::as<r_t>()), as<T>());
    return bit_cast(sub[if_(is_ltz(a)).else_(a)](s,a), as<r_t>());
  }
}
