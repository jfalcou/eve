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
  // Function decorator - numeric mode
  struct numeric_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using numeric_type = decorated<numeric_()>;
  inline constexpr numeric_type const numeric = {};
}
