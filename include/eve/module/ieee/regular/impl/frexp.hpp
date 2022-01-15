//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <eve/module/ieee/regular/ifrexp.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // tagged cases
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto frexp_(EVE_SUPPORTS(cpu_), raw_type const &, T const &a0) noexcept
  {
    auto [m, e] = raw(ifrexp)(a0);
    return kumi::make_tuple(m, to_<T>(e));
  }

  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto frexp_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    auto [m, e] = ifrexp(a0);
    return kumi::make_tuple(m, to_<T>(e));
  }
}
