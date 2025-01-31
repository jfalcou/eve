//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{

// *_impl in separate functions, as otherwise compiler can not
// choose overload between riscv-specific and common one

template<plain_scalar_value T, typename N, value U>
EVE_FORCEINLINE auto
self_geq_impl(wide<T, N> lhs, U rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (std::same_as<wide<T, N>, U> || scalar_value<U>)
{
  if constexpr( scalar_value<U> && !std::same_as<T, U> ) return self_geq(lhs, static_cast<T>(rhs));
  else
  {
    constexpr auto c = categorize<wide<T, N>>();
    if constexpr( match(c, category::int_) ) return __riscv_vmsge(lhs, rhs, N::value);
    else if constexpr( match(c, category::uint_) ) return __riscv_vmsgeu(lhs, rhs, N::value);
    else if constexpr( match(c, category::float_) ) return __riscv_vmfge(lhs, rhs, N::value);
  }
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_geq(wide<T, N> lhs, wide<T, N> rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>>
{
  return self_geq_impl(lhs, rhs);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_geq(wide<T, N> lhs, std::convertible_to<T> auto rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>>
{
  return self_geq_impl(lhs, rhs);
}

template<plain_scalar_value T, typename N, value U>
EVE_FORCEINLINE auto
self_leq_impl(wide<T, N> lhs, U rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (std::same_as<wide<T, N>, U> || scalar_value<U>)
{
  if constexpr( scalar_value<U> && !std::same_as<T, U> ) return self_leq(lhs, static_cast<T>(rhs));
  else
  {
    constexpr auto c = categorize<wide<T, N>>();
    if constexpr( match(c, category::int_) ) return __riscv_vmsle(lhs, rhs, N::value);
    else if constexpr( match(c, category::uint_) ) return __riscv_vmsleu(lhs, rhs, N::value);
    else if constexpr( match(c, category::float_) ) return __riscv_vmfle(lhs, rhs, N::value);
  }
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_leq(wide<T, N> lhs, wide<T, N> rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>>
{
  return self_leq_impl(lhs, rhs);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_leq(wide<T, N> lhs, std::convertible_to<T> auto rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>>
{
  return self_leq_impl(lhs, rhs);
}

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

template<plain_scalar_value T, typename N, value U>
EVE_FORCEINLINE auto
self_neq_impl(wide<T, N> lhs, U rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (std::same_as<wide<T, N>, U> || scalar_value<U>)
{
  if constexpr( scalar_value<U> && !std::same_as<T, U> ) return self_neq(lhs, static_cast<T>(rhs));
  else
  {
    constexpr auto c = categorize<wide<T, N>>();
    if constexpr( match(c, category::integer_) ) return __riscv_vmsne(lhs, rhs, N::value);
    else if constexpr( match(c, category::float_) ) return __riscv_vmfne(lhs, rhs, N::value);
  }
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_neq(wide<T, N> lhs, wide<T, N> rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>>
{
  return self_neq_impl(lhs, rhs);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_neq(wide<T, N> lhs, std::convertible_to<T> auto rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>>
{
  return self_neq_impl(lhs, rhs);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_eq(logical<wide<T, N>> lhs, logical<wide<T, N>> rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>>
{
  return __riscv_vmxnor(lhs, rhs, N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_neq(logical<wide<T, N>> lhs, logical<wide<T, N>> rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>>
{
  return __riscv_vmxor(lhs, rhs, N::value);
}
}
