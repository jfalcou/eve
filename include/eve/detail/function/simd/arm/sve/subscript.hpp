//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>

namespace eve::detail
{
template<typename T, typename N>
EVE_FORCEINLINE T
extract(wide<T, N> const& v, std::size_t i) noexcept requires sve_abi<abi_t<T, N>>
{
  return v.storage()[i];
}

template<typename T, typename N>
EVE_FORCEINLINE T
insert(wide<T, N>& v, std::size_t i, T x) noexcept requires sve_abi<abi_t<T, N>>
{
  return v.storage()[i] = x;
}

template<typename T, typename N>
EVE_FORCEINLINE logical<T>
extract(logical<wide<T, N>> const& v, std::size_t i) noexcept requires sve_abi<abi_t<T, N>>
{
  auto bits = [&]() -> typename logical<wide<T, N>>::bits_type
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( match(c, category::size8_) ) return svdup_u8_z(v, (std::uint8_t)-1);
    else if constexpr( match(c, category::size16_) ) return svdup_u16_z(v, (std::uint16_t)-1);
    else if constexpr( match(c, category::size32_) ) return svdup_u32_z(v, (std::uint32_t)-1);
    else if constexpr( match(c, category::size64_) ) return svdup_u64_z(v, (std::uint64_t)-1);
  }();

  return logical<T> {bits.get(i)};
}

template<typename T, typename N>
EVE_FORCEINLINE void
insert(logical<wide<T, N>>& v, std::size_t i, T x) noexcept requires sve_abi<abi_t<T, N>> = delete;

}
