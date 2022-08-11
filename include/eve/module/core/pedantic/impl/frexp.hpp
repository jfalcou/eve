//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/module/core/decorator/pedantic.hpp>
#include <eve/module/core/pedantic/ifrexp.hpp>
#include <eve/module/core/regular/converter.hpp>

namespace eve::detail
{
template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
frexp_(EVE_SUPPORTS(cpu_), pedantic_type const&, T const& a0) noexcept
{
  auto [m, e] = pedantic(ifrexp)(a0);
  return kumi::make_tuple(m, to_<T>(e));
}
}
