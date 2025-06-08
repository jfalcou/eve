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

namespace eve::detail
{
  template<callable_options O, typename T, typename N, typename U>
  EVE_FORCEINLINE logical<wide<T, N>> is_equal_(EVE_REQUIRES(rvv_), O const& opts, wide<T, N> a, U b) noexcept
    requires (rvv_abi<abi_t<T, N>> && same_element_type<T, U>)
  {
    if constexpr (O::contains(definitely))
    {
      return is_less.behavior(cpu_{}, opts, a, b);
    }
    else
    {
      constexpr auto c = categorize<wide<T, N>>();

      if      constexpr (match(c, category::int_))   return __riscv_vmslt(a, b, N::value);
      else if constexpr (match(c, category::uint_))  return __riscv_vmsltu(a, b, N::value);
      else if constexpr (match(c, category::float_)) return __riscv_vmflt(a, b, N::value);
    }
  }
}

/*

// *_impl in separate functions, as otherwise compiler can not
// choose overload between riscv-specific and common one

template<plain_scalar_value T, typename N, value U>
EVE_FORCEINLINE auto
self_eq_impl(wide<T, N> lhs, U rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (std::same_as<wide<T, N>, U> || scalar_value<U>)
{
  if constexpr( scalar_value<U> && !std::same_as<T, U> ) return self_eq(lhs, static_cast<T>(rhs));
  else
  {
    constexpr auto c = categorize<wide<T, N>>();
    if constexpr( match(c, category::integer_) ) return __riscv_vmseq(lhs, rhs, N::value);
    else if constexpr( match(c, category::float_) ) return __riscv_vmfeq(lhs, rhs, N::value);
  }
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_eq(wide<T, N> lhs, wide<T, N> rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>>
{
  return self_eq_impl(lhs, rhs);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_eq(wide<T, N> lhs, std::convertible_to<T> auto rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>>
{
  return self_eq_impl(lhs, rhs);
}
*/