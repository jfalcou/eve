//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  // Function decorator - splat mode
  struct splat_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using splat_type = decorated<splat_()>;
  [[maybe_unused]] inline constexpr splat_type const splat = {};
}
