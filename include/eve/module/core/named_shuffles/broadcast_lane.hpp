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
//!    @var broadcast_lane
//!    @brief a named shuffle for duplicating the lane across a register.
//!
//!    @note use eve::broadcast or a constructor to create a simd_value from
//!    a scalar value. This is a shuffle, for when the value is in register already.
//!
//!    **Defined in Header**
//!
//!    @code
//!    #include <eve/module/core.hpp>
//!    @endcode
//!
//!    As any named shuffle, allows to pass a group size, to treat multiple elements as one.
//!    Group size has to be 0 < G <= T::size()
//!
//!    @code
//!    template <simd_value T, std::ptrdiff_t G, std::ptrdiff_t I>
//!    T broadcast_lane(T x, eve::fixed<G>, eve::index_t<I>);  // (1)
//!
//!    template <simd_value T, std::ptrdiff_t I>
//!    T broadcast_lane(T x, eve::index_t<I>);  // (2)
//!    @endcode
//!
//!   **Parameters**
//!
//!    * x - simd_value to shuffle
//!    * G - (optional) - number of elements to treat as one.
//!    * I - index of the lane to broadcast
//!
//!   (2) calls (1) with G == 1;
//!   (1) broadcasts the group of size G in position I to all register.
//!
//!   **Return value**
//!
//!   shuffled register
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/named_shuffles/broadcast_lane.cpp}
//================================================================================================
struct broadcast_lane_t
{
  template<simd_value T, std::ptrdiff_t G, std::ptrdiff_t I>
  static consteval auto pattern(eve::as<T>, eve::fixed<G>, eve::index_t<I>)
  {
    static_assert(I < T::size() / G);
    return eve::fix_pattern<T::size() / G>([](int, int) { return I; });
  }

  template<simd_value T, std::ptrdiff_t G, std::ptrdiff_t I>
  static consteval std::ptrdiff_t level(eve::as<T> tgt, eve::fixed<G> g, eve::index_t<I> i)
  {
    constexpr std::size_t    reg_size = sizeof(element_type_t<T>) * T::size();
    constexpr std::ptrdiff_t g_size   = sizeof(element_type_t<T>) * G;

    if constexpr( eve::has_aggregated_abi_v<T> )
    {
      if constexpr( G == T::size() / 2 ) return 0;
      using half_t = decltype(T {}.slice(lower_));
      return level(as<half_t> {}, g, i);
    }
    else if constexpr( current_api >= vmx ) return 2;
    else if constexpr( current_api >= sve )
    {
      if constexpr ( !logical_value<T> ) return g_size > 8 ? 3 : 2;
      else if constexpr ( G == 1 ) return 4;
      else if constexpr ( g_size <= 8 ) return 6;
      else return 7;
    }
    else if constexpr( current_api >= neon )
    {
      if constexpr ( current_api >= asimd ) return 2;
      else if constexpr ( reg_size <= 8 ) return 2;
      else return 4;
    }

    // x86

    if constexpr (current_api == avx512 && logical_value<T>)
    {
      if constexpr (G == 1) return 4;
      else return level(detail::mask_type(tgt), g, i) + 4;
    }
    else if constexpr (reg_size == 64)
    {
      if constexpr (g_size >= 16) return 2;
      else if constexpr (g_size >= 2) return 3;
      else return 4;
    }
    else if constexpr (reg_size == 32)
    {
      if constexpr (g_size >= 16) return 2;
      if constexpr (current_api == avx) return 4;
      if constexpr (g_size >= 8) return 2;
      if constexpr (g_size >= 4) return 3;
      if constexpr (g_size >= 2 && current_api == avx512) return 3;
      else return 4;
    }
    else
    {
      if constexpr ( g_size >= 4 ) return 2;
      else if constexpr ( g_size == 2 && reg_size <= 8 ) return 2;
      else if constexpr ( current_api >= ssse3 ) return 3;
      else return 4;
    }
  }
};

inline constexpr auto broadcast_lane = detail::named_shuffle_1<broadcast_lane_t> {};
  //================================================================================================
  //!  @}
  //================================================================================================

}
