//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#if defined(EVE_INCLUDE_RISCV_HEADER)

#  ifndef __riscv_v_fixed_vlen
#    error __riscv_v_fixed_vlen must be defined
#  endif

namespace eve::detail
{
// natural lmul if > 0, frac otherwise
template<plain_scalar_value scalar_type, typename cardinal>
constexpr auto rvv_lmul_v = []
{
  constexpr std::ptrdiff_t m1_len       = __riscv_v_fixed_vlen;
  constexpr std::ptrdiff_t min_len      = m1_len * sizeof(scalar_type) / 8;
  std::ptrdiff_t           expected_len = sizeof(scalar_type) * 8 * cardinal::value;
  std::ptrdiff_t           reg_len      = std::max(min_len, expected_len);
  if( reg_len >= m1_len ) return static_cast<int>(reg_len / m1_len);
  else return -static_cast<int>(m1_len / reg_len);
}();

template<plain_scalar_value scalar_type, typename cardinal>
constexpr auto rvv_logical_ratio_v = []
{
  auto           lmul         = rvv_lmul_v<scalar_type, cardinal>;
  constexpr auto element_size = sizeof(scalar_type) * 8;
  return lmul > 0 ? element_size / lmul : element_size * (-lmul);
}();

template<plain_scalar_value T>
using rvv_m1_wide = wide<T, fixed<__riscv_v_fixed_vlen / 8 / sizeof(T)>>;
}
#endif
