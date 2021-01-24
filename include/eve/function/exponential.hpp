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
  EVE_MAKE_CALLABLE(exponential_, exponential);
}

#include <eve/module/real/stats/function/regular/generic/exponential.hpp>
#include <eve/module/real/stats/function/diff/generic/exponential.hpp>
#include <eve/module/real/stats/function/attributes/generic/exponential.hpp>
