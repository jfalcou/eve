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

  inline constexpr auto divisible_by_cardinal = rbr::flag<struct divisible_by_cardinal_tag>;

  inline constexpr auto no_aligning = rbr::flag<struct disable_aligning_tag>;


  template <typename Traits>
  constexpr std::ptrdiff_t get_unrolling() {
    if constexpr (!Traits::contains(eve::algo::unrolling)) return 1;
    else return std::remove_cvref_t<decltype(std::declval<Traits>()[unrolling])>{}();
  }

  // Temp hack while https://github.com/jfalcou/ofw/issues/25 is not done
  template <typename ... User, typename ... Default>
  constexpr auto default_to(traits<User...>, traits<Default...>) {
    using o_t = traits<User...>;
    using d_t = traits<Default...>;

    auto unroll_ = [&] (auto ...other){
           if constexpr (o_t::contains(unrolling)) return traits(unroll<get_unrolling<o_t>()>, other...);
      else if constexpr (d_t::contains(unrolling)) return traits(unroll<get_unrolling<d_t>()>, other...);
      else                                         return traits(other...);
    };

    auto divisible_ = [&] (auto ...other){
      if constexpr (o_t::contains(divisible_by_cardinal) ||
                    d_t::contains(divisible_by_cardinal))
      {
        return unroll_(divisible_by_cardinal, other...);
      }
      else
      {
        return unroll_(other...);
      }
    };

    auto no_aligning_ = [&] (auto ...other){
      if constexpr (o_t::contains(no_aligning) ||
                    d_t::contains(no_aligning))
      {
        return divisible_(no_aligning, other...);
      }
      else
      {
        return divisible_(other...);
      }
    };

    return no_aligning_();
  }
}
