//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
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
#include <eve/function/none.hpp>
#include <eve/function/count_true.hpp>
