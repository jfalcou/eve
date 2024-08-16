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
template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE logical<wide<T, N>>
                rvv_true()
{
  static constexpr auto   lmul  = riscv_rvv_dyn_::getLMUL<T>(N::value);
  static constexpr size_t size  = sizeof(T) * 8;
  static constexpr size_t ratio = lmul > 0 ? size / lmul : size * (-lmul);
  if constexpr( ratio == 1 ) return __riscv_vmset_m_b1(N::value);
  else if constexpr( ratio == 2 ) return __riscv_vmset_m_b2(N::value);
  else if constexpr( ratio == 4 ) return __riscv_vmset_m_b4(N::value);
  else if constexpr( ratio == 8 ) return __riscv_vmset_m_b8(N::value);
  else if constexpr( ratio == 16 ) return __riscv_vmset_m_b16(N::value);
  else if constexpr( ratio == 32 ) return __riscv_vmset_m_b32(N::value);
  else if constexpr( ratio == 64 ) return __riscv_vmset_m_b64(N::value);
}

template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE logical<wide<T, N>>
                rvv_none()
{
  static constexpr auto   lmul  = riscv_rvv_dyn_::getLMUL<T>(N::value);
  static constexpr size_t size  = sizeof(T) * 8;
  static constexpr size_t ratio = lmul > 0 ? size / lmul : size * (-lmul);
  if constexpr( ratio == 1 ) return __riscv_vmclr_m_b1(N::value);
  else if constexpr( ratio == 2 ) return __riscv_vmclr_m_b2(N::value);
  else if constexpr( ratio == 4 ) return __riscv_vmclr_m_b4(N::value);
  else if constexpr( ratio == 8 ) return __riscv_vmclr_m_b8(N::value);
  else if constexpr( ratio == 16 ) return __riscv_vmclr_m_b16(N::value);
  else if constexpr( ratio == 32 ) return __riscv_vmclr_m_b32(N::value);
  else if constexpr( ratio == 64 ) return __riscv_vmclr_m_b64(N::value);
}

template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE logical<wide<T, N>>
                rvv_one(size_t i)
{
  std::array<T, N::value> Vals = {};
  Vals[i]                      = 1;
  wide<T, N> Vector(Vals.begin(), Vals.end());
  return Vector != static_cast<T>(0);
}

}
