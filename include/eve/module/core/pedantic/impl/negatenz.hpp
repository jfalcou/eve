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
#include <eve/module/core/pedantic/signnz.hpp>
#include <eve/module/core/regular/all.hpp>

#include <concepts>

namespace eve::detail
{
template<ordered_value T>
EVE_FORCEINLINE T
negatenz_(EVE_SUPPORTS(cpu_),
          pedantic_type const&,
          T const& a,
          T const& b) noexcept requires has_native_abi_v<T>
{
  if constexpr( signed_value<T> ) { return a * pedantic(signnz)(b); }
  else { return a; }
}

template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
negatenz_(EVE_SUPPORTS(cpu_),
          pedantic_type const&,
          T const& a,
          U const& b) noexcept
-> decltype(negatenz(a, b))
{
  return arithmetic_call(pedantic(negatenz), a, b);
}

}
