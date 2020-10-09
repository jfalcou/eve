//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

// helper file to include all horizontal functions
#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(horizontal_, horizontal);
}

#include <eve/function/all.hpp>
#include <eve/function/any.hpp>
#include <eve/function/nbtrue.hpp>
#include <eve/function/none.hpp>
