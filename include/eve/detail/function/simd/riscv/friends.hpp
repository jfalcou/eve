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

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_greater(wide<T, N> lhs, wide<T, N> rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (!std::is_floating_point_v<T>)
{
  if constexpr( std::is_signed_v<T> ) return __riscv_vmsgt(lhs, rhs, N::value);
  else return __riscv_vmsgtu(lhs, rhs, N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_greater(wide<T, N> lhs, std::convertible_to<T> auto rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (!std::is_floating_point_v<T>)
{
  auto rhs_cast = static_cast<T>(rhs);
  if constexpr( std::is_signed_v<T> ) return __riscv_vmsgt(lhs, rhs_cast, N::value);
  else return __riscv_vmsgtu(lhs, rhs_cast, N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_greater(wide<T, N> lhs, wide<T, N> rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (std::is_floating_point_v<T>)
{
  return __riscv_vmfgt(lhs, rhs, N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_greater(wide<T, N> lhs, std::convertible_to<T> auto rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (std::is_floating_point_v<T>)
{
  return __riscv_vmfgt(lhs, static_cast<T>(rhs), N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_less(wide<T, N> lhs, wide<T, N> rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (!std::is_floating_point_v<T>)
{
  if constexpr( std::is_signed_v<T> ) return __riscv_vmslt(lhs, rhs, N::value);
  else return __riscv_vmsltu(lhs, rhs, N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_less(wide<T, N> lhs, std::convertible_to<T> auto rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (!std::is_floating_point_v<T>)
{
  auto rhs_cast = static_cast<T>(rhs);
  if constexpr( std::is_signed_v<T> ) return __riscv_vmslt(lhs, rhs_cast, N::value);
  else return __riscv_vmsltu(lhs, rhs_cast, N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_less(wide<T, N> lhs, wide<T, N> rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (std::is_floating_point_v<T>)
{
  return __riscv_vmflt(lhs, rhs, N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_less(wide<T, N> lhs, std::convertible_to<T> auto rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (std::is_floating_point_v<T>)
{
  return __riscv_vmflt(lhs, static_cast<T>(rhs), N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_geq(wide<T, N> lhs, wide<T, N> rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (!std::is_floating_point_v<T>)
{
  if constexpr( std::is_signed_v<T> ) return __riscv_vmsge(lhs, rhs, N::value);
  else return __riscv_vmsgeu(lhs, rhs, N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_geq(wide<T, N> lhs, std::convertible_to<T> auto rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (!std::is_floating_point_v<T>)
{
  auto rhs_cast = static_cast<T>(rhs);
  if constexpr( std::is_signed_v<T> ) return __riscv_vmsge(lhs, rhs_cast, N::value);
  else return __riscv_vmsgeu(lhs, rhs_cast, N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_geq(wide<T, N> lhs, wide<T, N> rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (std::is_floating_point_v<T>)
{
  return __riscv_vmfge(lhs, rhs, N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_geq(wide<T, N> lhs, std::convertible_to<T> auto rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (std::is_floating_point_v<T>)
{
  return __riscv_vmfge(lhs, static_cast<T>(rhs), N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_leq(wide<T, N> lhs, wide<T, N> rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (!std::is_floating_point_v<T>)
{
  if constexpr( std::is_signed_v<T> ) return __riscv_vmsle(lhs, rhs, N::value);
  else return __riscv_vmsleu(lhs, rhs, N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_leq(wide<T, N> lhs, std::convertible_to<T> auto rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (!std::is_floating_point_v<T>)
{
  auto rhs_cast = static_cast<T>(rhs);
  if constexpr( std::is_signed_v<T> ) return __riscv_vmsle(lhs, rhs_cast, N::value);
  else return __riscv_vmsleu(lhs, rhs_cast, N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_leq(wide<T, N> lhs, wide<T, N> rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (std::is_floating_point_v<T>)
{
  return __riscv_vmfle(lhs, rhs, N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_leq(wide<T, N> lhs, std::convertible_to<T> auto rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (std::is_floating_point_v<T>)
{
  return __riscv_vmfle(lhs, static_cast<T>(rhs), N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_eq(wide<T, N> lhs, wide<T, N> rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (!std::is_floating_point_v<T>)
{
  return __riscv_vmseq(lhs, rhs, N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_eq(wide<T, N> lhs, std::convertible_to<T> auto rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (!std::is_floating_point_v<T>)
{
  return __riscv_vmseq(lhs, static_cast<T>(rhs), N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_eq(wide<T, N> lhs, wide<T, N> rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (std::is_floating_point_v<T>)
{
  return __riscv_vmfeq(lhs, rhs, N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_eq(wide<T, N> lhs, std::convertible_to<T> auto rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (std::is_floating_point_v<T>)
{
  return __riscv_vmfeq(lhs, static_cast<T>(rhs), N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_neq(wide<T, N> lhs, wide<T, N> rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (!std::is_floating_point_v<T>)
{
  return __riscv_vmsne(lhs, rhs, N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_neq(wide<T, N> lhs, std::convertible_to<T> auto rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (!std::is_floating_point_v<T>)
{
  return __riscv_vmsne(lhs, static_cast<T>(rhs), N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_neq(wide<T, N> lhs, wide<T, N> rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (std::is_floating_point_v<T>)
{
  return __riscv_vmfne(lhs, rhs, N::value);
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_neq(wide<T, N> lhs, std::convertible_to<T> auto rhs) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>> && (std::is_floating_point_v<T>)
{
  return __riscv_vmfne(lhs, static_cast<T>(rhs), N::value);
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

template<typename T, typename U, typename N>
EVE_FORCEINLINE auto
self_logand(rvv_ const&, logical<wide<T, N>> v, logical<wide<U, N>> w) noexcept
    -> logical<wide<T, N>>
requires(rvv_abi<abi_t<T, N>> || rvv_abi<abi_t<U, N>>)
{
  if constexpr( !is_aggregated_v<abi_t<T, N>> && !is_aggregated_v<abi_t<U, N>> )
  {
    auto                casted_w = bit_cast(w, as<logical<wide<T, N>>> {});
    logical<wide<T, N>> to_ret   = __riscv_vmand(v, casted_w, N::value);
    return to_ret;
  }
  else
  {
    auto [lv, hv] = v.slice();
    auto [lw, hw] = w.slice();
    auto res      = logical<wide<T, N>> {lv && lw, hv && hw};
    return res;
  }
}

template<typename T, typename U, typename N>
EVE_FORCEINLINE auto
self_logor(rvv_ const&, logical<wide<T, N>> v, logical<wide<U, N>> w) noexcept
    -> logical<wide<T, N>>
requires(rvv_abi<abi_t<T, N>> || rvv_abi<abi_t<U, N>>)
{
  if constexpr( !is_aggregated_v<abi_t<T, N>> && !is_aggregated_v<abi_t<U, N>> )
  {
    auto                casted_w = bit_cast(w, as<logical<wide<T, N>>> {});
    logical<wide<T, N>> to_ret   = __riscv_vmor(v, casted_w, N::value);
    return to_ret;
  }
  else
  {
    auto [lv, hv] = v.slice();
    auto [lw, hw] = w.slice();
    return logical<wide<T, N>> {lv || lw, hv || hw};
  }
}

template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_lognot(logical<wide<T, N>> v) noexcept -> logical<wide<T, N>>
requires rvv_abi<abi_t<T, N>>
{
  return __riscv_vmnot(v, N::value);
}

}
