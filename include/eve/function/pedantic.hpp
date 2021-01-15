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
  template<auto Param> struct diff_;

  //================================================================================================
  // Function decorator - pedantic mode
  struct pedantic_
  {
    template<auto N> static constexpr auto combine( decorated<diff_<N>()> const& ) noexcept
    {
      return decorated<diff_<N>(pedantic_)>{};
    }
  };

  using pedantic_type = decorated<pedantic_()>;
  [[maybe_unused]] inline constexpr pedantic_type const pedantic = {};
}
