//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/module/core/regular/saturate.hpp>

namespace eve::detail
{
//////////////////////////////////////////////////////////////////////////////////////
// saturated case
//////////////////////////////////////////////////////////////////////////////////////
template<value T, scalar_value U>
EVE_FORCEINLINE auto
convert_(EVE_SUPPORTS(cpu_), saturated_type const&, T const& v0, as<U> const& tgt) noexcept
{
  return convert(saturate(v0, tgt), tgt);
}
}
