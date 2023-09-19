//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/shuffle_v2/idxm.hpp>
#include <eve/detail/shuffle_v2/shuffle_v2_fwd.hpp>
#include <eve/wide.hpp>

namespace eve::detail
{

template<std::ptrdiff_t G, std::ptrdiff_t... I, simd_value T>
EVE_FORCEINLINE auto
is_na_or_we_mask(eve::pattern_t<I...>, eve::fixed<G>, eve::as<T> tgt)
{
  if constexpr( G == 1 && logical_simd_value<T> ) return T {I >= 0 ...};
  else if constexpr( G == 1 )
  {
    using e_t = eve::element_type_t<T>;
    static_assert(std::unsigned_integral<e_t>);
    return T {(I < 0 ? 0 : (e_t)-1)...};
  }
  else
  {
    constexpr std::array idxs {I...};
    return is_na_or_we_mask(idxm::to_pattern<idxm::expand_group<G>(idxs)>(), eve::lane<1>, tgt);
  }
}

template <typename T, std::ptrdiff_t ...I>
EVE_FORCEINLINE
T make_idx_mask(eve::pattern_t<I...>, as<T>) {
  return T{I...};
}

template <auto p, typename T>
EVE_FORCEINLINE
T make_idx_mask(as<T> tgt) {
  return make_idx_mask(idxm::to_pattern<p>(), tgt);
}

template<simd_value T, std::ptrdiff_t G, std::ptrdiff_t... I>
struct expanded_pattern_t : pattern_t<I...>
{
  static constexpr std::array idxs = {I...};

  static constexpr std::ptrdiff_t e_t_size     = (int)sizeof(eve::element_type_t<T>);
  static constexpr std::ptrdiff_t g_size       = e_t_size * G;
  static constexpr std::ptrdiff_t reg_size     = T::size() * e_t_size;
  static constexpr std::ptrdiff_t out_reg_size = idxs.size() * g_size;

  // todo: avx512, sve - repace 0s with we
  static constexpr std::array idxs2match = idxs;

  static constexpr bool has_zeroes = idxm::has_zeroes(idxs);

  static constexpr std::array most_repeated = idxm::most_repeated_pattern<I...>;
  static constexpr std::array most_repeated_no_zeroes = idxm::replace_na(most_repeated, we_);

  static constexpr auto repeated_8  = idxm::repeated_pattern_of_size<8 / g_size, I...>;
  static constexpr auto repeated_16 = idxm::repeated_pattern_of_size<16 / g_size, I...>;
  static constexpr auto repeated_32 = idxm::repeated_pattern_of_size<32 / g_size, I...>;

  static constexpr auto shuffle_16_first = idxm::put_bigger_groups_in_position<16 / g_size>(idxs);
  static constexpr auto shuffle_8_first = idxm::put_bigger_groups_in_position<8 / g_size>(idxs);
  static constexpr auto shuffle_4_first = idxm::put_bigger_groups_in_position<4 / g_size>(idxs);
  static constexpr auto shuffle_2_first = idxm::put_bigger_groups_in_position<2 / g_size>(idxs);

  template <std::ptrdiff_t FirstSize>
  static constexpr auto shuffle_n_first(eve::fixed<FirstSize>)
  {
    if constexpr (FirstSize == 16) return shuffle_16_first;
    if constexpr (FirstSize == 8) return shuffle_8_first;
    if constexpr (FirstSize == 4) return shuffle_4_first;
    if constexpr (FirstSize == 2) return shuffle_2_first;
  }


  static constexpr std::array xy_swapped = idxm::swap_xy(idxs, std::ssize(idxs));
};

template<simd_value T, std::ptrdiff_t G, std::ptrdiff_t... I>
constexpr expanded_pattern_t<T, G, I...> expanded_pattern;

template<simd_value T, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_2_using_or(pattern_t<I...>, fixed<G> g, T x, T y)
{
  constexpr std::array idxs {I...};
  auto [x_, xl] = shuffle_v2_core(x, g, idxm::to_pattern<idxm::just_first_shuffle(idxs, na_)>());
  auto [y_, yl] = shuffle_v2_core(y, g, idxm::to_pattern<idxm::just_second_shuffle(idxs, na_)>());
  return kumi::tuple {x_ | y_, idxm::add_shuffle_levels(xl, yl, eve::index<2>)};
}

template <simd_value T>
constexpr auto mask_type(eve::as<T> tgt)
{
  if constexpr ( logical_simd_value<T> ) return eve::as<decltype(T {}.mask())>{};
  else return tgt;
}

}
