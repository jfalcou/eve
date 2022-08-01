//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>

namespace eve::detail
{

// Returns clear sve_true for type
// Calling svptrue_b8 is OK for most cases, where you OK with
// 1s in insignificant bits but sometimes you are not.
template<typename T>
svbool_t
sve_true()
{
  if constexpr( sizeof(T) == 1 ) return svptrue_b8();
  else if constexpr( sizeof(T) == 2 ) return svptrue_b16();
  else if constexpr( sizeof(T) == 4 ) return svptrue_b32();
  else if constexpr( sizeof(T) == 8 ) return svptrue_b64();
}

} // namespace eve::detail
