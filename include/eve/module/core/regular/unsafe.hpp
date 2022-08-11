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
// Function decorator - unsafe mode
struct unsafe_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
};

using unsafe_type                         = decorated<unsafe_()>;
inline constexpr unsafe_type const unsafe = {};
}
