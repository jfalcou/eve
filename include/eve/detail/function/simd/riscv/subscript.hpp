//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/riscv/rvv_common_masks.hpp>

namespace eve::detail
{
template<callable_options O, typename T, typename N>
EVE_FORCEINLINE T
extract_(EVE_REQUIRES(rvv_), O const&, wide<T, N> v, std::size_t i) noexcept
requires rvv_abi<abi_t<T, N>>
{
  auto on_first_needed = __riscv_vslidedown_tu(v, v, i, N::value);
  if constexpr( std::is_floating_point_v<T> ) return __riscv_vfmv_f(on_first_needed);
  else return __riscv_vmv_x(on_first_needed);
}

template<callable_options O, typename T, typename N>
EVE_FORCEINLINE void
insert_(EVE_REQUIRES(rvv_),
        O const&,
        wide<T, N>                & v,
        std::size_t                 i,
        std::convertible_to<T> auto x) noexcept
requires rvv_abi<abi_t<T, N>>
{
  // get mask with 1 on i'th element.
  logical<wide<T, N>> mask {[i](int j, int) { return j == i; }};
  v = if_else(mask, static_cast<T>(x), v);
}

template<callable_options O, typename T, typename N>
EVE_FORCEINLINE logical<T>
extract_(EVE_REQUIRES(rvv_), O const&, logical<wide<T, N>> v, std::size_t i) noexcept
requires rvv_abi<abi_t<T, N>>
{
  constexpr size_t                      array_size = (N::value + 7) / 8;
  std::array<unsigned char, array_size> mask_data;
  __riscv_vsm(mask_data.data(), v, N::value);
  size_t needed_element_id = i / 8;
  return mask_data[needed_element_id] & (1 << (i % 8));
}

// For riscv logical we can not rely on common algorithm.
template<callable_options O, typename T, typename N>
EVE_FORCEINLINE logical<T>
extract_(EVE_REQUIRES(rvv_), O const&, logical<wide<T, N>> v, std::size_t i) noexcept
{
  using Wide  = logical<wide<T, N>>;
  using abi_t = typename Wide::abi_type;
  if constexpr( has_aggregated_abi_v<Wide> )
  {
    constexpr auto sz = Wide::size() / 2;
    if( i < sz ) return extract(v.slice(lower_), i);
    else return extract(v.slice(upper_), i - sz);
  }
  else { static_assert("[eve riscv] -- should not be called"); }
}
// For riscv logical we can not rely on common algorithm.
template<callable_options O, typename T, typename N, typename Value>
EVE_FORCEINLINE void
insert_(EVE_REQUIRES(rvv_), O const&, logical<wide<T, N>>& p, std::size_t i, Value v) noexcept
{
  using Wide = logical<wide<T, N>>;
  if constexpr( has_aggregated_abi_v<Wide> )
  {
    constexpr auto sz = Wide::size() / 2;
    auto [l, h]       = p.slice();

    if( i < sz ) insert(l, i, v);
    else insert(h, i - sz, v);

    p = Wide {l, h};
  }
  else if constexpr( has_emulated_abi_v<Wide> ) { p.storage()[i] = v; }
  else static_assert("[eve riscv] -- should not be called");
}

template<callable_options O, typename T, typename N>
EVE_FORCEINLINE void
insert_(EVE_REQUIRES(rvv_),
        O const&,
        logical<wide<T, N>>          & v,
        std::size_t                    i,
        std::convertible_to<bool> auto x) noexcept
requires rvv_abi<abi_t<T, N>>
{
  constexpr size_t                      array_size = (N::value + 7) / 8;
  std::array<unsigned char, array_size> mask_data;
  unsigned char                        *ptr = mask_data.data();
  __riscv_vsm(ptr, v, N::value);
  size_t needed_element_id = i / 8;
  if( static_cast<bool>(x) ) mask_data[needed_element_id] |= (1 << (i % 8));
  else mask_data[needed_element_id] &= ~(1 << (i % 8));
  constexpr auto ratio = rvv_logical_ratio_v<T, N>;
  if constexpr( ratio == 1 ) v = __riscv_vlm_v_b1(ptr, N::value);
  else if constexpr( ratio == 2 ) v = __riscv_vlm_v_b2(ptr, N::value);
  else if constexpr( ratio == 4 ) v = __riscv_vlm_v_b4(ptr, N::value);
  else if constexpr( ratio == 8 ) v = __riscv_vlm_v_b8(ptr, N::value);
  else if constexpr( ratio == 16 ) v = __riscv_vlm_v_b16(ptr, N::value);
  else if constexpr( ratio == 32 ) v = __riscv_vlm_v_b32(ptr, N::value);
  else if constexpr( ratio == 64 ) v = __riscv_vlm_v_b64(ptr, N::value);
  else static_assert("[eve riscv] -- unexpected ratio for logical");
}

}
