//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  // Rounding decorator objects
  struct upward_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  struct downward_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  struct to_nearest_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  struct toward_zero_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using upward_type      = decorated<upward_()>;
  using downward_type    = decorated<downward_()>;
  using to_nearest_type  = decorated<to_nearest_()>;
  using toward_zero_type = decorated<toward_zero_()>;

  inline constexpr upward_type      const upward       = {};
  inline constexpr downward_type    const downward     = {};
  inline constexpr to_nearest_type  const to_nearest   = {};
  inline constexpr toward_zero_type const toward_zero  = {};
}
