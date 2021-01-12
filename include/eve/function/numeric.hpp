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
  // Function decorator - numeric mode
  struct numeric_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using numeric_type = decorated<numeric_()>;
  inline constexpr numeric_type const numeric = {};
}
