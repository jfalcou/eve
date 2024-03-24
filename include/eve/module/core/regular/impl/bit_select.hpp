//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/bit_andnot.hpp>
#include <eve/module/core/regular/bit_or.hpp>

namespace eve::detail
{

  template<typename T, typename U, typename M, callable_options O>
  EVE_FORCEINLINE constexpr bit_value_t<T, U, M>
  bit_select_(EVE_REQUIRES(cpu_), O const&, M m, T u, U v) noexcept
  {
    return bit_or(bit_and(u, m), bit_andnot(v, m));
  }
}
