//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/rem.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var fmod
//!   @brief Alias of eve::pedantic(eve::rem).
//! @}
//================================================================================================
constexpr auto fmod = eve::pedantic(eve::rem);
}
