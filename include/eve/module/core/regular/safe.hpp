//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
// Function decorator - safe mode
struct safe_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
};

using safe_type                       = decorated<safe_()>;
inline constexpr safe_type const safe = {};
}
