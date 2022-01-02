//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/pattern.hpp>
#include <bit>
#include <optional>

namespace eve
{
  EVE_MAKE_CALLABLE(broadcast_group_, broadcast_group);
}

#include <eve/module/real/core/function/regular/generic/broadcast_group.hpp>
