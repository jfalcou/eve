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
#include <eve/module/core/regular/convert.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
template<scalar_value T, scalar_value U>
EVE_FORCEINLINE auto
logical_xor_(EVE_SUPPORTS(cpu_), logical<T> const& a, logical<U> const& b) noexcept
{
  return as_logical_t<T> {a.value() != b.value()};
}

template<simd_value T, simd_value U>
EVE_FORCEINLINE auto
logical_xor_(EVE_SUPPORTS(cpu_), logical<T> const& a, logical<U> const& b) noexcept
requires (cardinal_v<T> == cardinal_v<U>)
{
  return bit_cast ( a.bits() != convert(b, as<logical<element_type_t<T>>>()).bits()
                  , as<logical<T>>()
                  );
}

template<simd_value T, scalar_value U>
EVE_FORCEINLINE auto
logical_xor_(EVE_SUPPORTS(cpu_), logical<T> const& a, logical<U> const& b) noexcept
{
  return logical_xor(a, as_logical_t<T>(b.value()));
}

template<scalar_value T, simd_value U>
EVE_FORCEINLINE auto
logical_xor_(EVE_SUPPORTS(cpu_), logical<T> const& a, logical<U> const& b) noexcept
{
  using r_t = as_wide_t<logical<T>, cardinal_t<U>>;
  return logical_xor( bit_cast(b,as<r_t>{}),a);
}

template<logical_value T>
EVE_FORCEINLINE auto
logical_xor_(EVE_SUPPORTS(cpu_), T a, bool b) noexcept
{
  return T {b} != a;
}

template<logical_value U>
EVE_FORCEINLINE auto
logical_xor_(EVE_SUPPORTS(cpu_), bool a, U b) noexcept
{
  return U {a} != b;
}

EVE_FORCEINLINE auto
logical_xor_(EVE_SUPPORTS(cpu_), bool a, bool b) noexcept
{
  return a != b;
}
}
