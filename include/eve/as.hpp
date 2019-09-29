//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_AS_HPP_INCLUDED
#define EVE_AS_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <type_traits>
#include <cstdint>

namespace eve
{
  template<typename T>
  struct as_
  {
    using type = T;
  };

  template<typename T>
  EVE_FORCEINLINE constexpr as_<std::decay_t<T>> as(T &&) noexcept
  {
    return {};
  }

  // Predefine type objects
  inline constexpr auto const double_ = as_<double>{};
  inline constexpr auto const single_ = as_<float> {};
  inline constexpr auto const uint8_  = as_<std::uint8_t> {};
  inline constexpr auto const uint16_ = as_<std::uint16_t>{};
  inline constexpr auto const uint32_ = as_<std::uint32_t>{};
  inline constexpr auto const uint64_ = as_<std::uint64_t>{};
  inline constexpr auto const int8_   = as_<std::int8_t>  {};
  inline constexpr auto const int16_  = as_<std::int16_t> {};
  inline constexpr auto const int32_  = as_<std::int32_t> {};
  inline constexpr auto const int64_  = as_<std::int64_t> {};
}

#endif
