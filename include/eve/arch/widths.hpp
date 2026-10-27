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

#include <eve/deps/kumi.hpp>
#include <eve/arch/spec.hpp>
#include <eve/arch/abi.hpp>

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
  //! eve::lanes_t wraps an integral power of two constant that represents the number of lanes in a
  //! given eve::simd_value type.
  //
  //!  @tparam Width Number of lane. If `Width` is not a power of two, code is invalid.
  //!
  //!  @groupheader{Member type}
  //!
  //!   | Member          | Definition                                                    |
  //!   |:----------------|:--------------------------------------------------------------|
  //!   | `type`          | `eve::lanes_t``<Width>`                                      |
  //!   | `split_type`    | `eve::lanes_t``<Width / 2>`. Only defined if `Width` > 1  |
  //!   | `combined_type` | `eve::lanes_t``<Width * 2>`                                  |
  //!
  //================================================================================================
  template<width_type Width>
  struct lanes_t : std::integral_constant<width_type, Width>
  {
    static_assert(is_valid_width<Width>, "Width must be a non-zero power of 2");

    using type          = lanes_t<Width>;
    using split_type    = lanes_t<Width / 2>;
    using combined_type = lanes_t<Width * 2>;
  };

  template<> struct lanes_t<1ULL> : std::integral_constant<width_type, 1ULL>
  {
    using type          = lanes_t<1ULL>;
    using combined_type = lanes_t<2>;
  };

  template<width_type Width>
  inline constexpr lanes_t<Width> const lanes = {};

  //! Deprecated spelling of a width. Pass the width itself: wide<T, 4> rather than
  //! wide<T, fixed<4>>.
  template<width_type Width>
  [[deprecated("eve::fixed<N> is deprecated, pass the width itself: wide<T, N>")]]
  inline constexpr width_type fixed = Width;

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

  namespace _
  {
    template<typename ABI, typename Leaves>
    extern width_type fundamental_width_of_v;

    template<typename ABI, typename... Ls>
    constexpr inline width_type fundamental_width_of_v<ABI, kumi::tuple<Ls...>> =
      kumi::_::min((ABI::template fundamental_width<Ls>)...);

    template<typename ABI, typename Leaves>
    extern width_type expected_width_of_v;

    template<typename ABI, typename... Ls>
    constexpr inline width_type expected_width_of_v<ABI, kumi::tuple<Ls...>> =
      kumi::_::min((ABI::template expected_width<Ls>)...);
  }
  //================================================================================================
  //! @addtogroup eve_arch
  //! @{
  //!   @brief Computes the fundamental width of a given type
  //!
  //!   **Required header:** `#include <eve/arch/widths.hpp>`
  //!
  //!   @ref eve::fundamental_width_v computes the width of the smallest register able to store
  //!   values of type `Type` for a given SIMD `ABI` with no uninitialized lanes.
  //!
  //!   @tparam Type  Type of value to assess
  //!   @tparam ABI   SIMD ABI to use as reference. Must models eve::regular_abi.
  //!
  //! @}
  //================================================================================================
  template<typename Type, regular_abi ABI = eve::current_abi_type>
  constexpr inline width_type fundamental_width_v = ABI::template fundamental_width<Type>;

  template<eve::product_type Type, regular_abi ABI>
  constexpr inline width_type fundamental_width_v<Type, ABI> = _::fundamental_width_of_v<ABI, kumi::result::flatten_all_t<Type>>;

  //================================================================================================
  //! @addtogroup eve_arch
  //! @{
  //!   @brief Computes the expected width of a given type
  //!
  //!   **Required header:** `#include <eve/arch/widths.hpp>`
  //!
  //!   @ref eve::expected_width_v is the exact width type of the register able to store
  //!   values of type `Type` for a given SIMD `ABI` as a native register type.
  //!
  //!   @tparam Type  Type of value to assess
  //!   @tparam ABI   SIMD ABI to use as reference. Must models eve::regular_abi.
  //!
  //! @}
  //================================================================================================
  template<typename Type, regular_abi ABI = eve::current_abi_type>
  inline constexpr width_type expected_width_v = ABI::template expected_width<Type>;

  template<eve::product_type Type, regular_abi ABI>
  inline constexpr width_type expected_width_v<Type, ABI> = _::expected_width_of_v<ABI, kumi::result::flatten_all_t<Type>>;
}

namespace eve
{
  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!   @struct width
  //!   @brief Computes the width of a given type
  //!
  //!   **Required header:** `#include <eve/arch/widths.hpp>`
  //!
  //!   For a given type `T`, computes the type of its width.
  //!
  //!   @tparam T Type to process
  //!
  //!   #### Member types
  //!
  //!   |Name   | Definition               |
  //!   |:------|:-------------------------|
  //!   |`type` | The width type of `T` |
  //!
  //!    <br/>
  //!
  //!   @groupheader{Helper types}
  //!
  //!   @code{.cpp}
  //!   template<typename Type>
  //!   using width_t = typename width<Type>::type;
  //!   @endcode
  //!
  //!   @groupheader{Helper variable template}
  //!
  //!   @code{.cpp}
  //!   template<typename Type>
  //!   inline constexpr auto width_v = width<Type>::value;
  //!   @endcode
  //! @}
  //================================================================================================
  template<typename Type>
  inline constexpr width_type width_v = 1;

  template<typename Type>
  requires( !std::same_as<Type, std::remove_cvref_t<Type>> )
  inline constexpr width_type width_v<Type> = width_v<std::remove_cvref_t<Type>>;

  template<typename Type>
  using width_t = lanes_t<width_v<Type>>;
}
