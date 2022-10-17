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
//! @addtogroup core_arithmetic
//! @{
//!   @var fmod
//!   @brief Alias of eve::pedantic(eve::rem).
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(fmod_, fmod);
}

#include <eve/module/core/regular/impl/fmod.hpp>
