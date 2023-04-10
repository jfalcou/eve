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
//================================================================================================
//================================================================================================
// Function decorators mark-up used in function overloads
  struct aos_
  {
    template<typename D> static constexpr auto combine(D const&) noexcept = delete;
  };

  using aos_type = decorated<aos_()>;
  [[maybe_unused]] inline constexpr aos_type const aos = {};

  struct soa_
  {
    template<typename D> static constexpr auto combine(D const&) noexcept = delete;
  };

  using soa_type = decorated<soa_()>;
  [[maybe_unused]] inline constexpr soa_type const soa = {};
}
