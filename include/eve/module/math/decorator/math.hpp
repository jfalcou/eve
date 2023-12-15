//======================================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//======================================================================================================================
#pragma once

#include <eve/module/math/decorator/trigo_tags.hpp>

//======================================================================================================================
// New option style  - TODO rename later without the '2'
//======================================================================================================================
#include <eve/detail/raberu.hpp>

namespace eve
{
  struct full_circle_mode     {};
  struct quarter_circle_mode  {};
  struct half_circle_mode     {};
  struct medium_mode          {};
  struct big_mode             {};

  [[maybe_unused]] inline constexpr auto const big2             = ::rbr::flag( big_mode{}             );
  [[maybe_unused]] inline constexpr auto const full_circle2     = ::rbr::flag( full_circle_mode{}     );
  [[maybe_unused]] inline constexpr auto const half_circle2     = ::rbr::flag( half_circle_mode{}     );
  [[maybe_unused]] inline constexpr auto const medium2          = ::rbr::flag( medium_mode{}          );
  [[maybe_unused]] inline constexpr auto const quarter_circle2  = ::rbr::flag( quarter_circle_mode{}  );

  struct big_option             : detail::exact_option<big2>            {};
  struct full_circle_option     : detail::exact_option<full_circle2>    {};
  struct half_circle_option     : detail::exact_option<half_circle2>    {};
  struct medium_option          : detail::exact_option<medium2>         {};
  struct quarter_circle_option  : detail::exact_option<quarter_circle2> {};

  // ----------------------------------------------------------------------------------
  // [TEMPORARY] Will be removed when all decorator have been converted
  // ----------------------------------------------------------------------------------
  inline constexpr auto as_option(full_circle_type    const&) { return full_circle2;    }
  inline constexpr auto as_option(quarter_circle_type const&) { return quarter_circle2; }
  inline constexpr auto as_option(half_circle_type    const&) { return half_circle2;    }
  inline constexpr auto as_option(detail::medium_type const&) { return medium2;         }
  inline constexpr auto as_option(detail::big_type    const&) { return big2;            }
}
