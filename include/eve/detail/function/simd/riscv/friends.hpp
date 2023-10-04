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

#ifdef RVV_LOGIC
#  error RVV_LOGIC defined
#endif

#define RVV_LOGIC(eve_name, int_func, unsigned_func, fp_func)                                      \
  template<plain_scalar_value T, typename N>                                                       \
  EVE_FORCEINLINE auto eve_name(wide<T, N> lhs, wide<T, N> rhs) noexcept -> logical<wide<T, N>>    \
  requires rvv_abi<abi_t<T, N>> && (!std::is_floating_point_v<T>)                                  \
  {                                                                                                \
    if constexpr( std::is_signed_v<T> ) return int_func(lhs, rhs, N::value);                       \
    else return unsigned_func(lhs, rhs, N::value);                                                 \
  }                                                                                                \
  template<plain_scalar_value T, typename N>                                                       \
  EVE_FORCEINLINE auto eve_name(wide<T, N> lhs, std::convertible_to<T> auto rhs) noexcept          \
      -> logical<wide<T, N>>                                                                       \
  requires rvv_abi<abi_t<T, N>> && (!std::is_floating_point_v<T>)                                  \
  {                                                                                                \
    if constexpr( std::is_signed_v<T> ) return int_func(lhs, static_cast<T>(rhs), N::value);       \
    else return unsigned_func(lhs, static_cast<T>(rhs), N::value);                                 \
  }                                                                                                \
  template<plain_scalar_value T, typename N>                                                       \
  EVE_FORCEINLINE auto eve_name(wide<T, N> lhs, wide<T, N> rhs) noexcept -> logical<wide<T, N>>    \
  requires rvv_abi<abi_t<T, N>> && (std::is_floating_point_v<T>)                                   \
  {                                                                                                \
    logical<wide<T, N>> res = fp_func(lhs, rhs, N::value);                                         \
    return res;                                                                                    \
  }                                                                                                \
  template<plain_scalar_value T, typename N>                                                       \
  EVE_FORCEINLINE auto eve_name(wide<T, N> lhs, std::convertible_to<T> auto rhs) noexcept          \
      -> logical<wide<T, N>>                                                                       \
  requires rvv_abi<abi_t<T, N>> && (std::is_floating_point_v<T>)                                   \
  {                                                                                                \
    return fp_func(lhs, static_cast<T>(rhs), N::value);                                            \
  }

RVV_LOGIC(self_greater, __riscv_vmsgt, __riscv_vmsgtu, __riscv_vmfgt)
RVV_LOGIC(self_less, __riscv_vmslt, __riscv_vmsltu, __riscv_vmflt)
RVV_LOGIC(self_geq, __riscv_vmsge, __riscv_vmsgeu, __riscv_vmfge)
RVV_LOGIC(self_leq, __riscv_vmsle, __riscv_vmsleu, __riscv_vmfle)
RVV_LOGIC(self_eq, __riscv_vmseq, __riscv_vmseq, __riscv_vmfeq)
RVV_LOGIC(self_neq, __riscv_vmsne, __riscv_vmsne, __riscv_vmfne)

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

#undef RVV_LOGIC

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
