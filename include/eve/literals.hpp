//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/cardinals.hpp>
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
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //! @defgroup literal Custom literal suffix
  //! @brief  SIMD types related literal suffixes
  //!
  //! **EVE** provides various user-defined literal suffixes to simplify the definition of constants
  //! in some of its API. Using them requires the following include and namespace usage:
  //!
  //! @code
  //! using namespace eve::literal;
  //! #include <eve/literals.hpp>
  //! @endcode
  //!
  //! @groupheader{Index literals}
  //! Some **EVE** function requires a constexpr constant as a parameter to identify a lane or an
  //! an index in some of **EVE** components. The `_idx` suffix allows for a fast way to specify
  //! such constant
  //!
  //! @code
  //! using namespace eve::literal;
  //! eve::wide<float, eve::fixed<4>> x = {0.1,0.01,0.001,0.0001};
  //!
  //! // Broadcast 1st element of x into y
  //! auto y = eve::broadcast(x, 0_idx);
  //! @endcode
  //!
  //! @groupheader{Wide literals}
  //! Suffixes are provided to construct a eve::wide instance from a literal constant.
  //!
  //! @code
  //! using namespace eve::literal;
  //! // x is a eve::wide<short>
  //! auto x = 45_wi16;
  //!
  //! // x is a eve::wide<float>
  //! auto y = 2.635_wf;
  //! @endcode
  //! @}
  //================================================================================================

  //================================================================================================
  //! @addtogroup literal
  //! @{
  //================================================================================================

  //! @brief Constructs a literal index
  template<char... c> constexpr auto operator"" _idx()
  {
    return index<detail::parse<c...>()>;
  }

  //! @brief Constructs a literal eve::wide<double> from the value d
  inline auto operator""_w(long double d) noexcept { return wide<double>(d); }

  //! @brief Constructs a literal eve::wide<float> from the value d
  inline auto operator""_wf(long double d) noexcept { return wide<float>(d); }

  //! @brief Constructs a literal eve::wide<std::int64_t> from the value d
  inline auto operator""_wi64(unsigned long long int d) noexcept { return wide<std::int64_t>(d); }

  //! @brief Constructs a literal eve::wide<std::int32_t> from the value d
  inline auto operator""_wi32(unsigned long long int d) noexcept { return wide<std::int32_t>(d); }

  //! @brief Constructs a literal eve::wide<std::int16_t> from the value d
  inline auto operator""_wi16(unsigned long long int d) noexcept { return wide<std::int16_t>(d); }

  //! @brief Constructs a literal eve::wide<std::int8_t> from the value d
  inline auto operator""_wi8(unsigned long long int d) noexcept { return wide<std::int8_t>(d); }

  //! @brief Constructs a literal eve::wide<std::uint64_t> from the value d
  inline auto operator""_wu64(unsigned long long int d) noexcept { return wide<std::uint64_t>(d); }

  //! @brief Constructs a literal eve::wide<std::uint32_t> from the value d
  inline auto operator""_wu32(unsigned long long int d) noexcept { return wide<std::uint32_t>(d); }

  //! @brief Constructs a literal eve::wide<std::uint16_t> from the value d
  inline auto operator""_wu16(unsigned long long int d) noexcept { return wide<std::uint16_t>(d); }

  //! @brief Constructs a literal eve::wide<std::uint8_t> from the value d
  inline auto operator""_wu8(unsigned long long int d) noexcept { return wide<std::uint8_t>(d); }
  //================================================================================================
  //! @}
  //================================================================================================
}
