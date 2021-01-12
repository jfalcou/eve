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
  // Function decorators mark-up used in function overloads
  struct saturated_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using saturated_type = decorated<saturated_()>;

  //================================================================================================
  // Function decorator - saturated mode
  inline constexpr saturated_type const saturated = {};
}
