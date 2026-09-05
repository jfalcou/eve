//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <cstddef>
#include <type_traits>

namespace eve
{
  namespace _ {
    static constexpr bool is_pow2(std::ptrdiff_t v) { return !v || ( !(v & (v - 1)) ); }
  }

  using width_type = std::ptrdiff_t;

  template<width_type Width>
  concept is_valid_width = (Width > 0) && _::is_pow2(Width);

  //================================================================================================
  //! @addtogroup eve_simd_types
  //! @{
  //================================================================================================

  //================================================================================================
  //! @brief SIMD register width type
  //!
  //! eve::fixed wraps an integral power of two constant that represents the number of lanes in a
  //! given eve::simd_value type.
  //
  //!  @tparam Width Number of lane. If `Width` is not a power of two, code is invalid.
  //!
  //!  @groupheader{Member type}
  //!
  //!   | Member          | Definition                                                    |
  //!   |:----------------|:--------------------------------------------------------------|
  //!   | `type`          | `eve::fixed``<Width>`                                      |
  //!   | `split_type`    | `eve::fixed``<Width / 2>`. Only defined if `Width` > 1  |
  //!   | `combined_type` | `eve::fixed``<Width * 2>`                                  |
  //!
  //================================================================================================
  template<width_type Width>
  struct fixed : std::integral_constant<width_type, Width>
  {
    static_assert(is_valid_width<Width>, "Width must be a non-zero power of 2");

    using type          = fixed<Width>;
    using split_type    = fixed<Width / 2>;
    using combined_type = fixed<Width * 2>;
  };

  template<> struct fixed<1ULL> : std::integral_constant<width_type, 1ULL>
  {
    using type          = fixed<1ULL>;
    using combined_type = fixed<2>;
  };

  namespace _ {

  template <typename>
  struct is_wide_width  : std::false_type {};

  template <std::ptrdiff_t N>
  struct is_wide_width<eve::fixed<N>> : std::true_type {};

  }  // namespace _

  template<std::ptrdiff_t Width>
  inline constexpr fixed<Width> const lane = {};

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
  //! @}
  //================================================================================================

  //================================================================================================
  // Hardware-agnostic width
  //================================================================================================
  namespace _
  {
    template<typename T>
    constexpr width_type cache_line_width = 64 / sizeof(T);
  }

  //================================================================================================
  //! @ingroup eve_simd_concepts
  //! @brief concept to determine if this is width type of a wide
  //!
  //! @tparam T
  //!
  //! only true if T is instance of `eve::fixed`.
  //!
  //! This concept is needed to define some other concepts, unlikely to be useful on it's own.
  //================================================================================================
  template <typename T>
  concept wide_width = _::is_wide_width<T>::value;
}
