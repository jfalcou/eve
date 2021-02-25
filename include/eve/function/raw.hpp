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
  // Function decorator - raw mode
  struct raw_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using raw_type = decorated<raw_()>;
  inline constexpr raw_type const raw = {};
}
