//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_LITERALS_HPP_INCLUDED
#define EVE_LITERALS_HPP_INCLUDED

#include <eve/arch/wide.hpp>
#include <type_traits>
#include <cstddef>

namespace eve::detail
{
  template<std::uint64_t N>
  using idx_ = std::integral_constant<std::uint64_t, N>;

  template<char... c>
  constexpr std::uint64_t parse()
  {
    std::uint64_t value = 0;
    char          arr[] = {c...};
    for(std::size_t i = 0; i < sizeof...(c); ++i) value = value * 10 + (arr[ i ] - 48);
    return value;
  }
}

namespace eve::literal
{
  // integral constants
  template<char... c>
  constexpr auto operator"" _c()
  {
    return detail::idx_<detail::parse<c...>()>{};
  }

  // wide generator
  inline auto operator""_w(long double d) noexcept { return wide<double>(d); }
  inline auto operator""_wf(long double d) noexcept { return wide<float>(d); }
  inline auto operator""_wi64(unsigned long long int d) noexcept { return wide<std::int64_t>(d); }
  inline auto operator""_wi32(unsigned long long int d) noexcept { return wide<std::int32_t>(d); }
  inline auto operator""_wi16(unsigned long long int d) noexcept { return wide<std::int16_t>(d); }
  inline auto operator""_wi8(unsigned long long int d) noexcept { return wide<std::int8_t>(d); }
  inline auto operator""_wu64(unsigned long long int d) noexcept { return wide<std::uint64_t>(d); }
  inline auto operator""_wu32(unsigned long long int d) noexcept { return wide<std::uint32_t>(d); }
  inline auto operator""_wu16(unsigned long long int d) noexcept { return wide<std::uint16_t>(d); }
  inline auto operator""_wu8(unsigned long long int d) noexcept { return wide<std::uint8_t>(d); }
}

#endif
