//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr as_integer_t<T>
  bitinteger( T const &a) noexcept
  {
    using r_t = as_integer_t<T>;
    r_t a0 = bit_cast(a, as<r_t>());
    return if_else(is_gez(a0), a0, signmask(eve::as<r_t>())- a0 );
  }

  template<typename T>
  EVE_FORCEINLINE constexpr as_floating_point_t<T>
  bitfloating( T const &a) noexcept
  {
    using r_t = as_floating_point_t<T>;
   T s = bit_cast(signmask(eve::as<r_t>()), as<T>());
    return bit_cast(if_else(is_gez(a), a, s-a), as<r_t>());
  }

}
