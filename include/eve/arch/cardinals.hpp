//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <cstddef>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================

  //================================================================================================
  //! @brief SIMD register cardinal type
  //!
  //! eve::fixed wraps an integral power of two constant that represents the number of lanes in a
  //! given eve::simd_value type.
  //
  //!  @tparam Cardinal Number of lane. If `Cardinal` is not a power of two, code is invalid.
  //!
  //!  @groupheader{Member type}
  //!
  //!   | Member          | Definition                                                    |
  //!   |:----------------|:--------------------------------------------------------------|
  //!   | `type`          | `eve::fixed``<Cardinal>`                                      |
  //!   | `split_type`    | `eve::fixed``<Cardinal / 2>`. Only defined if `Cardinal` > 1  |
  //!   | `combined_type` | `eve::fixed``<Cardinal * 2>`                                  |
  //!
  //================================================================================================
  template<std::ptrdiff_t Cardinal>
  struct fixed : std::integral_constant<std::ptrdiff_t, Cardinal>
  {
    static constexpr bool is_pow2(std::ptrdiff_t v) { return !v || ( !(v & (v - 1)) ); }
    static_assert(is_pow2(Cardinal), "Cardinal must be a power of 2");

    using type          = fixed<Cardinal>;
    using split_type    = fixed<Cardinal / 2>;
    using combined_type = fixed<Cardinal * 2>;
  };

  template<> struct fixed<1ULL> : std::integral_constant<std::ptrdiff_t, 1ULL>
  {
    using type          = fixed<1ULL>;
    using combined_type = fixed<2>;
  };


  //================================================================================================
  //! @brief Cardinal type for scalar values
  //================================================================================================
  struct scalar_cardinal : std::integral_constant<std::ptrdiff_t, 1ULL>
  {
    using type          = scalar_cardinal;
    using combined_type = fixed<2>;
  };

  //================================================================================================
  //! @brief Cardinal object representing the cardinal of [scalar values](@ref eve::scalar_value)
  //================================================================================================
  inline constexpr scalar_cardinal const scalar = {};

  template<std::ptrdiff_t Cardinal>
  inline constexpr fixed<Cardinal> const lane = {};

  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  // Constant index template class
  //================================================================================================
  template<std::ptrdiff_t Index>
  struct index_t : std::integral_constant<std::ptrdiff_t, Index>
  {};

  //================================================================================================
  // Template inline object for passing index within a wide
  //================================================================================================
  template<std::ptrdiff_t N> inline constexpr auto index = index_t<N>{};

  //================================================================================================
  // Hardware-agnostic cardinal
  //================================================================================================
  namespace detail
  {
    template<typename T> using cache_line_cardinal = fixed<64 / sizeof(T)>;
  }
}
