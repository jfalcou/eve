//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/meta.hpp>
#include <eve/module/core/regular/all.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename A0, typename A1>
  EVE_FORCEINLINE bool assert_good_shift(A1 const &t) noexcept
  {
    using v1_t = element_type_t<A1>;
    constexpr v1_t Mx  = sizeof(element_type_t<A0>) * 8;

    if constexpr(std::is_unsigned_v<element_type_t<A1>>)
    {
      return eve::all( t < Mx );
    }
    else
    {
      return eve::all( (t < Mx) && (t > -Mx) );
    }
  }
}
