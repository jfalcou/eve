//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/vectorized.hpp>

#include <type_traits>
#include <concepts>
#include <bit>

namespace eve
{
  template <typename W0, typename W1, typename... Ws>
  concept combinable = std::has_single_bit(sizeof...(Ws) + 2)
                        && simd_value<W0>
                        && std::same_as<W0, W1>
                        && (std::same_as<W0, Ws> && ...);

  template <typename Tgt, typename W0, typename W1, typename... Ws>
  concept combinable_to = combinable<W0, W1, Ws...>
                          && simd_value<Tgt>
                          && std::same_as<typename W0::value_type, typename Tgt::value_type>
                          && (W0::size() * (sizeof...(Ws) + 2)) == Tgt::size();
}
