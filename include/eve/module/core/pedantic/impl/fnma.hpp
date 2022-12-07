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
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/decorator/pedantic.hpp>
#include <eve/module/core/pedantic/fma.hpp>
#include <eve/module/core/regular/all.hpp>

#include <type_traits>

namespace eve::detail
{
template<ordered_value T, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
fnma_(EVE_SUPPORTS(cpu_),
      pedantic_type const&,
      T const& a,
      U const& b,
      V const& c) noexcept
-> decltype(fsm(a, b, c))
{
  return arithmetic_call(pedantic(fnma), a, b, c);
}

template<ordered_value T>
EVE_FORCEINLINE T
fnma_(EVE_SUPPORTS(cpu_),
      pedantic_type const&,
      T const& a,
      T const& b,
      T const& c) noexcept requires has_native_abi_v<T>
{
  return pedantic(fma)(T(-a), b, c);
}
}
