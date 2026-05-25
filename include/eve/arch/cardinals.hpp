//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/meta.hpp>

#include <cstddef>
#include <type_traits>
#include <concepts>
#include <compare>
#include <bit>

namespace eve
{
  template<typename T>
  concept natural = std::integral<T> && !std::same_as<T, bool>;

  struct size
  {
    consteval size(natural auto v) : value(v)
    {
      if (!std::has_single_bit(static_cast<std::size_t>(v)))
      {
        throw "[eve] Size must be a non-zero power of 2";
      }
    }

    constexpr operator int() const { return value; }

    friend constexpr bool operator==(size l, size r) noexcept { return l.value == r.value; }
    friend constexpr bool operator==(size s, natural auto n) noexcept { return s.value == static_cast<int>(n); }
    friend constexpr bool operator==(natural auto n, size s) noexcept { return s.value == static_cast<int>(n); }

    friend constexpr auto operator<=>(size l, size r) noexcept { return l.value <=> r.value; }
    friend constexpr auto operator<=>(size s, natural auto n) noexcept { return s.value <=> static_cast<int>(n); }
    friend constexpr auto operator<=>(natural auto n, size s) noexcept { return static_cast<int>(n) <=> s.value; }

    int value;
  };

  template<>
  struct translation_of<size>
  {
    using type = int;
  };

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
    static_assert((Cardinal > 0) && is_pow2(Cardinal), "Cardinal must be a non-zero power of 2");

    using type          = fixed<Cardinal>;
    using split_type    = fixed<Cardinal / 2>;
    using combined_type = fixed<Cardinal * 2>;
  };

  template<> struct fixed<1ULL> : std::integral_constant<std::ptrdiff_t, 1ULL>
  {
    using type          = fixed<1ULL>;
    using combined_type = fixed<2>;
  };

  namespace _ {

  template <typename>
  struct is_wide_cardinal  : std::false_type {};

  template <std::ptrdiff_t N>
  struct is_wide_cardinal<eve::fixed<N>> : std::true_type {};

  }  // namespace _

  template<std::ptrdiff_t Cardinal>
  inline constexpr fixed<Cardinal> const lane = {};

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
  // Hardware-agnostic cardinal
  //================================================================================================
  namespace _
  {
    template<typename T>
    constexpr size cache_line_cardinal = 64 / sizeof(T);
  }

  //================================================================================================
  //! @ingroup simd_concepts
  //! @brief concept to determine if this is cardinal type of a wide
  //!
  //! @tparam T
  //!
  //! only true if T is instance of `eve::fixed`.
  //!
  //! This concept is needed to define some other concepts, unlikely to be useful on it's own.
  //================================================================================================
  template <typename T>
  concept wide_cardinal = _::is_wide_cardinal<T>::value;
}
