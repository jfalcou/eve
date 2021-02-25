//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
