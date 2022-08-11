//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/function/interleave.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
EVE_MAKE_CALLABLE(interleave_shuffle_, interleave_shuffle);
}

namespace eve::detail
{
template<simd_value Wide>
EVE_FORCEINLINE auto
interleave_shuffle_(EVE_SUPPORTS(cpu_), Wide a, Wide b) noexcept
{
  auto [l, h] = interleave(a, b);
  return as_wide_t<element_type_t<Wide>, typename cardinal_t<Wide>::combined_type> {l, h};
}

template<simd_value Wide, scalar_value U>
EVE_FORCEINLINE auto
interleave_shuffle_(EVE_SUPPORTS(cpu_), Wide a, U b) noexcept
{
  return interleave_shuffle_(EVE_RETARGET(cpu_), a, Wide(b));
}

template<simd_value Wide, scalar_value U>
EVE_FORCEINLINE auto
interleave_shuffle_(EVE_SUPPORTS(cpu_), U a, Wide b) noexcept
{
  return interleave_shuffle_(EVE_RETARGET(cpu_), Wide(a), b);
}
}
