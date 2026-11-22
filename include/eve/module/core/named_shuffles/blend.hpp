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

EVE_NAMESPACE
{

//================================================================================================
//! @addtogroup eve_core_named_shuffles
//! @{
//!    @var blend
//!    @brief a named shuffle for mixing 2 registers together, without changing positions.
//!    @note You might be looking for `eve::if_else_`.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!    (TODO: support mixing more than 2 registers)
//!
//!    Accepts a pattern with just 0 and 1 that indicates number of the element for the current
//!    slot
//!
//!    blend([0, 1, 2, 3], [4, 5, 6, 7], pattern<1, 0, 0, 1>) -> [4, 1, 2, 7].
//!
//!    As any named shuffle, allows to specify a group size.
//!
//!    @code
//!    template<simd_value T, std::ptrdiff_t G, std::ptrdiff_t ...I>  // (1)
//!    T blend(T x, T y, lanes_t<G>, pattern_t<I...>)
//!    template<simd_value T, std::ptrdiff_t G>
//!    T blend(T x, T y, lanes_t<G>, pattern_formula auto gen)
//!
//!    template<simd_value T, std::ptrdiff_t ...I> // (2)
//!    T blend(T x, T y, pattern_t<I...>)
//!    template<simd_value T, std::ptrdiff_t ...I>
//!    T blend(T x, T y, pattern_formula auto gen)
//!    @endcode
//!
//!   **Parameters**
//!
//!     * x, y - values to shuffle.
//!     * G - (optional) - number of elements to treat as one.
//!     * pattern - how to shuffle elements
//!        I == 0 -> take a group from x
//!        I == 1 -> take a group from y
//!     * gen - eve::pattern_formula = alternative way to specify a pattern,
//!             computing it from index and size.
//!
//!    **Return value**
//!
//!      Returns a register with elements selected according to the mask.
//!
//!    @groupheader{Example}
//!
//!  @godbolt{doc/core/named_shuffles/blend.cpp}
//================================================================================================
struct blend_t
{
  template<simd_value T, std::ptrdiff_t G, std::ptrdiff_t... I>
  static constexpr auto pattern(eve::as<T>, eve::as<T>, eve::lanes_t<G>, pattern_t<I...>)
  {
    static_assert(((0 <= I && I <= 1) && ...), "pattern for blend has to only contain 0 and 1");
    static_assert(pattern_t<I...>::size() * G == T::size(), "pattern has wrong number of elements");

    return eve::fix_pattern<T::size() / G>(
        [](int i, int size)
        {
          constexpr std::array idxs {I...};
          return idxs[i] * size + i % size;
        });
  }

  template<simd_value T, std::ptrdiff_t G, std::ptrdiff_t... I>
  static constexpr std::ptrdiff_t level(eve::as<T>, eve::as<T>, eve::lanes_t<G> g, pattern_t<I...> p)
  {
    if constexpr( sizeof...(I) == 1 ) return 0;
    else if constexpr( eve::aggregated_abi<T> )
    {
      using half_t = decltype(T {}.slice(lower_));

      auto [p0, p1] = _::idxm::slice_pattern<pattern_t<I...>::size() / 2>(p);

      return std::max(level(as<half_t> {}, as<half_t> {}, g, p0),
                      level(as<half_t> {}, as<half_t> {}, g, p1));
    }

    if( ((I == 0) && ...) ) return 0;
    if( ((I == 1) && ...) ) return 0;

    if( current_api >= sve ) return logical_simd_value<T> ? 6 : 2;
    if( current_api >= avx512 ) return logical_simd_value<T> ? 6 : 2;
    if( current_api >= vmx ) return 3;

    const std::ptrdiff_t g_size       = sizeof(element_type_t<T>) * G;
    const std::size_t    reg_size     = sizeof(element_type_t<T>) * T::size();
    const std::size_t    count_from_x = ((I == 0) + ...);
    const std::size_t    count_from_y = ((I == 1) + ...);

    if( current_api >= neon )
    {
      if( current_api >= asimd && (count_from_x == 1 || count_from_y == 1) ) return 2;
      return 3;
    }

    if( current_api >= sse2 )
    {
      if constexpr( current_api == avx && reg_size >= 32 && g_size <= 2 )
      {
        using half_t  = decltype(T {}.slice(lower_));
        auto [p0, p1] = _::idxm::slice_pattern<pattern_t<I...>::size() / 2>(p);
        auto l0       = level(as<half_t> {}, as<half_t> {}, g, p0);
        auto l1       = level(as<half_t> {}, as<half_t> {}, g, p1);
        return _::idxm::add_shuffle_levels(l0, l1, 4);
      }
      if( current_api >= sse4_1 )
      {
        // the driver merges neighbours coming from the same register into bigger groups
        constexpr std::array    from {I...};
        constexpr std::ptrdiff_t merged_g_size = [&]
        {
          std::ptrdiff_t merged = 1;
          for( std::size_t step = 1; step < from.size(); step *= 2 )
          {
            for( std::size_t i = 0; i < from.size(); i += 2 * step )
            {
              if( from[i] != from[i + step] ) return merged;
            }
            merged *= 2;
          }
          return merged;
        }() * sizeof(element_type_t<T>) * G;

        if( merged_g_size >= 4 ) return 2;
        if( merged_g_size < 2 ) return 3;

        // _mm_blend_epi16, smaller registers are padded to 16 bytes
        if( reg_size <= 16 ) return 2;

        // _mm256_blend_epi16 shares the immediate between 16 byte lanes
        constexpr std::size_t half = sizeof...(I) / 2;
        for( std::size_t i = 0; i != half; ++i )
        {
          if( from[i] != from[i + half] ) return 3;
        }
        return 2;
      }

      if( g_size >= 8 ) return 2;
      if( g_size == 2 && reg_size == 4 ) return 6;
      return 7;
    }

    return 2;
  }

  template<simd_value T, std::ptrdiff_t G>
  static constexpr auto
  pattern(eve::as<T> tgt, eve::as<T>, eve::lanes_t<G> g, pattern_formula auto gen)
  {
    return pattern(tgt, tgt, g, fix_pattern<T::size() / G>(gen));
  }

  template<simd_value T, std::ptrdiff_t G, std::ptrdiff_t... I>
  static constexpr auto level(eve::as<T> tgt, eve::as<T>, eve::lanes_t<G> g, pattern_formula auto gen)
  {
    return level(tgt, tgt, g, fix_pattern<T::size() / G>(gen));
  }
};

inline constexpr auto blend = _::named_shuffle_2<blend_t> {};
  //================================================================================================
  //!  @}
  //================================================================================================

}
