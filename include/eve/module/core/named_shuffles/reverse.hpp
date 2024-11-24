//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/named_shuffles/named_shuffle_utils.hpp>
#include <eve/module/core/regular/shuffle_v2.hpp>

namespace eve
{

//================================================================================================
//! @addtogroup core_named_shuffles
//! @{
//!    @var reverse
//!    @brief a named shuffle for reversing a register.
//!
//!   **Defined in Header**
//!
//!    @code
//!    #include <eve/module/core.hpp>
//!    @endcode
//!
//!    As any named shuffle, allows to pass a group size, to treat multiple elements as one.
//!    Group size has to be 0 < G <= T::size()
//!
//!    @code
//!    template <simd_value T, std::ptrdiff_t G>
//!    T reverse(T x, eve::fixed<G>);  // (1)
//!
//!    template <simd_value T>
//!    T reverse(T x);  // (2)
//!    @endcode
//!
//!   **Parameters**
//!
//!    * x - simd_value to shuffle
//!    * G - (optional) - number of elements to treat as one.
//!
//!   (2) calls (1) with G == 1;
//!   (1) reverses positions of adjacent groups of elements of size G
//!
//!  **Return value**
//!
//!    Return x where groups of contiguous G elements are reversed.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/named_shuffles/reverse.cpp}
//!
//================================================================================================
struct reverse_t
{
  template<simd_value T, std::ptrdiff_t G> static consteval auto pattern(eve::as<T>, eve::fixed<G>)
  {
    return eve::fix_pattern<T::size() / G>([](int i, int size) { return size - i - 1; });
  }

  template<simd_value T, std::ptrdiff_t G>
  static consteval std::ptrdiff_t level(eve::as<T> tgt, eve::fixed<G> g)
  {
    if constexpr( eve::has_aggregated_abi_v<T> )
    {
      if constexpr( G == T::size() / 2 ) return 0;
      else
      {
        using half_t = decltype(T {}.slice(lower_));
        return level(as<half_t> {}, g);
      }
    }
    else
    {
      constexpr std::ptrdiff_t g_size     = sizeof(element_type_t<T>) * G;
      constexpr std::size_t    reg_size   = sizeof(element_type_t<T>) * T::size();
      constexpr bool is_expected_cardinal = T::size() == eve::expected_cardinal_v<element_type_t<T>>;

      if constexpr ( current_api >= sve )
      {
        if constexpr ( !logical_value<T> )
        {
          if constexpr ( reg_size <= 8 ) return 2;
          else if constexpr ( is_expected_cardinal && g_size <= 8 ) return 2;
          else if constexpr ( is_expected_cardinal && g_size == reg_size / 2 ) return 2;
          else return 3;
        }
        else if constexpr ( is_expected_cardinal && g_size <= 8 ) return 2;
        else return level(detail::mask_type(tgt), g) + 4;
      }

      else if constexpr (current_api >= neon) {
        if constexpr ( reg_size <= 8 ) return 2;
        if constexpr ( g_size == 8 ) return 2;
        if constexpr ( current_api >= asimd ) return 3;
        else return 4;
      }

      else if constexpr ( current_api >= vmx ) return 3;

      else if constexpr ( current_api == avx512 && logical_value<T> ) { return level(detail::mask_type(tgt), g) + 4; }

      else if constexpr ( current_api >= avx2 && reg_size >= 32 )
      {
        if constexpr ( g_size >= 16 ) return 2;
        else if constexpr ( g_size >= 8 ) return reg_size == 64 ? 3 : 2;
        else if constexpr ( g_size >= 4 ) return 3;
        else if constexpr ( g_size == 2 && current_api >= avx512 ) return 3;
        else return 5;
      }

      else if constexpr ( current_api == avx && reg_size >= 32 )
      {
        if constexpr ( g_size >= 16 ) return 2;
        else if constexpr ( g_size >= 4 ) return 4;
        else if constexpr ( g_size == 2 && current_api >= avx512 ) return 3;
        else return 9;
      }

      else if constexpr ( g_size >= 4 ) return 2;
      else if constexpr ( g_size == 2 && reg_size <= 8 ) return 2;

      else if constexpr ( current_api >= ssse3 ) return 3;

      else if constexpr ( g_size == 2 ) return 6;

      // chars on sse2
      else if constexpr ( reg_size == 2 ) return 6;

      // swap chars + reverse shorts
      else if constexpr ( reg_size <= 8 ) return 8;
      else return 12;
    }
  }
};

inline constexpr auto reverse = detail::named_shuffle_1<reverse_t> {};
  //================================================================================================
  //!  @}
  //================================================================================================
}
