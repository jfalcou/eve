//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/riscv/rvv_utils.hpp>

namespace eve::detail
{
template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE logical<wide<T, N>>
                rvv_true()
{
  static constexpr size_t ratio = rvv_logical_ratio_v<T, N>;
  if constexpr( ratio == 1 ) return __riscv_vmset_m_b1(N::value);
  else if constexpr( ratio == 2 ) return __riscv_vmset_m_b2(N::value);
  else if constexpr( ratio == 4 ) return __riscv_vmset_m_b4(N::value);
  else if constexpr( ratio == 8 ) return __riscv_vmset_m_b8(N::value);
  else if constexpr( ratio == 16 ) return __riscv_vmset_m_b16(N::value);
  else if constexpr( ratio == 32 ) return __riscv_vmset_m_b32(N::value);
  else if constexpr( ratio == 64 ) return __riscv_vmset_m_b64(N::value);
}

}
