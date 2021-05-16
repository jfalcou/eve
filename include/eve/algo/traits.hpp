//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/raberu.hpp>

#include <eve/arch/cardinals.hpp>

#include <type_traits>
#include <utility>

namespace eve::algo
{
  template <typename Settings>
  struct traits : Settings
  {
    template <rbr::keyword_parameter... Options>
    constexpr explicit traits(Options && ... options) : Settings(std::forward<Options>(options) ...) {}
  };

  template <typename ... Options>
  traits(Options&& ... options) -> traits<decltype(rbr::settings(std::forward<Options>(options) ...))>;

  inline constexpr auto unrolling = rbr::keyword<struct unrolling>;

  template<int N>
  inline constexpr auto unroll = (unrolling = eve::index<N>);
  inline constexpr auto divisible_by_cardinal = rbr::keyword<struct divisible_by_cardinal_tag>;

  template <typename Traits>
  constexpr std::ptrdiff_t get_unrolling() {
    if constexpr (!Traits::contains(eve::algo::unrolling)) return 1;
    else return std::remove_cvref_t<decltype(std::declval<Traits>()[unrolling])>{}();
  }
}
