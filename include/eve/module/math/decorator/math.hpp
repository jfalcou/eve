//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

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

  [[maybe_unused]] inline constexpr auto const big             = ::rbr::flag( big_mode{}             );
  [[maybe_unused]] inline constexpr auto const full_circle     = ::rbr::flag( full_circle_mode{}     );
  [[maybe_unused]] inline constexpr auto const half_circle     = ::rbr::flag( half_circle_mode{}     );
  [[maybe_unused]] inline constexpr auto const medium          = ::rbr::flag( medium_mode{}          );
  [[maybe_unused]] inline constexpr auto const quarter_circle  = ::rbr::flag( quarter_circle_mode{}  );

  struct big_option             : detail::exact_option<big>            {};
  struct full_circle_option     : detail::exact_option<full_circle>    {};
  struct half_circle_option     : detail::exact_option<half_circle>    {};
  struct medium_option          : detail::exact_option<medium>         {};
  struct quarter_circle_option  : detail::exact_option<quarter_circle> {};
}
