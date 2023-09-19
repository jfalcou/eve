//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/named_shuffles/named_shuffle_utils.hpp>
#include <eve/module/core/named_shuffles/reverse.hpp>
#include <eve/module/core/named_shuffles/swap_adjacent.hpp>
#include <eve/module/core/regular/shuffle_v2.hpp>

namespace eve
{

//================================================================================================
//! @addtogroup core_named_shuffles
//! @{
//!    @var reverse_in_subgroups
//!    @brief a named shuffle for reversing all subgroups in a register
//!
//!   **Defined in Header**
//!
//!    @code
//!    #include <eve/module/core.hpp>
//!    @endcode
//!
//!    As any named shuffle, allows to pass a group size, to treat multiple elements as one.
//!    Group size has to be 0 < G <= T::size()
//!    Subgroup size has to be 1 <= SubG <= T::size() / G
//!
//!    @note SubG == T::size() makes this function equivalent eve::reverse.
//!
//!    @code
//!    template <simd_value T, std::ptrdiff_t G, std::ptrdiff_t SubG>
//!    T reverse_in_subgroups(T x, eve::fixed<G>, eve::fixed<SubG>);  // (1)
//!
//!    template <simd_value T, std::ptrdiff_t SubG>
//!    T reverse_in_subgroups(T x, eve::fixed<SubG>); // (2)
//!    @endcode
//!
//!   **Parameters**
//!
//!    * x - simd_value to shuffle
//!    * G - (optional) - number of elements to treat as one.
//!    * SubG - size of a subgroup
//!
//!   (2) calls (1) with G == 1;
//!   (1) within each SubG reverses positions elements
//!
//!   **Return value**
//!
//!     Returns x where each subgroup is reversed.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/named_shuffles/reverse_in_subgroups.cpp}
//!
//================================================================================================
struct reverse_in_subgroups_t
{
  template<simd_value T, std::ptrdiff_t G, std::ptrdiff_t SubG>
  static constexpr auto pattern(eve::as<T>, eve::fixed<G>, eve::fixed<SubG>)
  {
    static_assert(SubG <= T::size() / G);
    static_assert(SubG >= 1);

    return eve::fix_pattern<T::size() / G>(
        [](int i, int)
        {
          int sub_pos    = i / SubG;
          int in_sub_pos = i % SubG;
          return sub_pos * SubG + SubG - in_sub_pos - 1;
        });
  }

  template<simd_value T, std::ptrdiff_t G, std::ptrdiff_t SubG>
  static constexpr std::ptrdiff_t level(eve::as<T> tgt, eve::fixed<G> g, eve::fixed<SubG> sub_g)
  {
    const std::ptrdiff_t g_size   = sizeof(element_type_t<T>) * G;
    const std::size_t    sub_size = g_size * SubG;
    const std::size_t    reg_size   = sizeof(element_type_t<T>) * T::size();

    if constexpr( SubG == 1 ) return 0;
    else if constexpr( SubG == 2 ) return swap_adjacent.level(tgt, g);
    else if constexpr( SubG == T::size() / G ) return reverse.level(tgt, g);
    else if constexpr( eve::has_aggregated_abi_v<T> )
    {
      if constexpr( G == T::size() / 2 ) return 0;
      using half_t = decltype(T {}.slice(lower_));
      return level(as<half_t> {}, g, sub_g);
    }

    if( current_api >= sve )
    {
      if( !logical_value<T> )
      {
        if( sub_size <= 8 ) return 2;
        return 3;
      }
      return level(detail::mask_type(tgt), g, sub_g) + 4;
    }

    if( current_api >= vmx ) return 3;
    if( current_api >= neon ) return 2;

    if( current_api == avx512 && logical_value<T> )
    {
      return level(detail::mask_type(tgt), g, sub_g) + 4;
    }

    if (sub_size == 32) {
      if (g_size == 8) return 2;
      if (g_size == 4) return 3;
      return 5;
    }

    if( g_size >= 4 ) return 2;

    if (current_api == avx && reg_size == 32) return 9;

    if( current_api >= ssse3 ) return 3;

    if( g_size == 2 ) return 4;
    if (reg_size <= 8) return 8;
    return 10;
  }
};

inline constexpr auto reverse_in_subgroups = detail::named_shuffle_1<reverse_in_subgroups_t> {};

}
