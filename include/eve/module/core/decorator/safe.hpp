//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  // TODO DOC
  //================================================================================================
  // Function decorator - safe mode
  struct safe_
  {
    template<typename D> static constexpr auto combine(D const&) noexcept = delete;
  };

  using safe_type                       = decorated<safe_()>;
  inline constexpr safe_type const safe = {};

  //TODO DOC
  //================================================================================================
  // Function decorator - unsafe mode
  struct unsafe_
  {
    template<typename D> static constexpr auto combine(D const&) noexcept = delete;
  };

  using unsafe_type                         = decorated<unsafe_()>;
  inline constexpr unsafe_type const unsafe = {};
}
