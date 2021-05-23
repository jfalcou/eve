//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/pedantic/ifrexp.hpp>
#include <eve/function/pedantic.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto frexp_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a0) noexcept
  {
    auto [m, e] = pedantic(ifrexp)(a0);
    return kumi::make_tuple(m, to_<T>(e));
  }
}
