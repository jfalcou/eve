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
template<typename T, typename N>
EVE_FORCEINLINE T
extract(wide<T, N> const& v, std::size_t i) noexcept
requires rvv_abi<abi_t<T, N>>
{
  auto OnFirstNeeded = __riscv_vslidedown_tu(v, v, i, N::value);
  if constexpr( std::is_floating_point_v<T> ) return __riscv_vfmv_f(OnFirstNeeded);
  else return __riscv_vmv_x(OnFirstNeeded);
}

template<typename T, typename N>
EVE_FORCEINLINE void
insert(wide<T, N>& v, std::size_t i, std::convertible_to<T> auto x) noexcept
requires rvv_abi<abi_t<T, N>>
{
  // get mask with 1 on i'th element.
  auto mask = rvv_one<T, N>(i);
  v         = if_else(mask, static_cast<T>(x), v);
}

template<typename T, typename N>
EVE_FORCEINLINE logical<T>
                extract(logical<wide<T, N>> const                &v, std::size_t i) noexcept
requires rvv_abi<abi_t<T, N>>
{
  using u_m1_cardinal               = typename riscv_rvv_dyn_::m1_fixed<unsigned>;
  using inter_type                  = wide<unsigned, u_m1_cardinal>;
  auto             uint_wide        = bit_cast(v, as<inter_type> {});
  constexpr size_t sew              = sizeof(unsigned) * 8;
  size_t           expected_element = i / sew;
  auto             val              = extract(uint_wide, expected_element);
  bool             to_ret           = std::bitset<sew>(val)[i % sew];
  return to_ret;
}

// For riscv logical we can not rely on common algorithm.
template<typename T, typename N>
EVE_FORCEINLINE logical<T>
                extract(logical<wide<T, N>> const                &v, std::size_t i) noexcept
{
  using Wide  = logical<wide<T, N>>;
  using abi_t = typename Wide::abi_type;

  if constexpr( has_bundle_abi_v<Wide> )
  {
    return kumi::apply([=](auto const&...m) { return typename Wide::value_type {m.get(i)...}; },
                       v.storage());
  }
  else if constexpr( has_aggregated_abi_v<Wide> )
  {
    constexpr auto sz = Wide::size() / 2;
    if( i < sz ) return extract(v.slice(lower_), i);
    else return extract(v.slice(upper_), i - sz);
  }
  else { static_assert("[eve riscv] -- should not be called"); }
}
// For riscv logical we can not rely on common algorithm.
template<typename T, typename N, typename Value>
EVE_FORCEINLINE void
insert(logical<wide<T, N>>& p, std::size_t i, Value v) noexcept
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
  else if constexpr( has_bundle_abi_v<Wide> )
  {
    kumi::for_each([i](auto& m, auto w) { m.set(i, w); }, p.storage(), v);
  }
  else static_assert("[eve riscv] -- should not be called");
}

template<typename T, typename N>
EVE_FORCEINLINE void
insert(logical<wide<T, N>>& v, std::size_t i, std::convertible_to<bool> auto x) noexcept
requires rvv_abi<abi_t<T, N>>
{
  using u_m1_cardinal               = typename riscv_rvv_dyn_::m1_fixed<unsigned>;
  using inter_type                  = wide<unsigned, u_m1_cardinal>;
  auto             uint_wide        = bit_cast(v, as<inter_type> {});
  constexpr size_t sew              = sizeof(unsigned) * 8;
  size_t           expected_element = i / sew;
  auto             val              = extract(uint_wide, expected_element);
  auto             new_bits         = std::bitset<sew>(val);
  new_bits[i % sew]                 = static_cast<bool>(x);
  unsigned new_val                  = new_bits.to_ullong();
  insert(uint_wide, expected_element, new_val);
  v = bit_cast(uint_wide, as<logical<wide<T, N>>> {});
}

}
