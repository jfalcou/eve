//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <cstddef>

namespace eve
{
  template<std::ptrdiff_t Cardinal>
  struct fixed : std::integral_constant<std::ptrdiff_t, Cardinal>
  {
    static constexpr bool is_pow2(std::ptrdiff_t v) { return !v || ( !(v & (v - 1)) ); }
    static_assert(is_pow2(Cardinal), "Cardinal must be a power of 2");

    using type          = fixed<Cardinal>;
    using split_type    = fixed<Cardinal / 2>;
    using combined_type = fixed<Cardinal * 2>;
  };

  template<>
  struct fixed<1ULL> : std::integral_constant<std::ptrdiff_t, 1ULL>
  {
    using type          = fixed<1ULL>;
    using combined_type = fixed<2>;
  };

  struct scalar_cardinal : std::integral_constant<std::ptrdiff_t, 1ULL>
  {
    using type          = scalar_cardinal;
    using combined_type = fixed<2>;
  };

  //================================================================================================
  // Cardinal template inline object for passing cardinal values to functions like load/store
  //================================================================================================
  inline constexpr scalar_cardinal const scalar = {};

  template<std::ptrdiff_t Cardinal>
  inline constexpr fixed<Cardinal> const lane = {};
}

