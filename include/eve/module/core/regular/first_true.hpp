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
//! @addtogroup core_horizontal
// DOC TO DO
//================================================================================================
EVE_MAKE_CALLABLE(first_true_, first_true);
}

#include <eve/arch.hpp>
#include <eve/module/core/regular/impl/first_true.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/first_true.hpp>
#endif
