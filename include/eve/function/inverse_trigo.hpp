//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

// helper file to include all inverse trigonometric functions
#include <eve/function/acos.hpp>
#include <eve/function/acosd.hpp>
#include <eve/function/acot.hpp>
#include <eve/function/acotd.hpp>
#include <eve/function/acsc.hpp>
#include <eve/function/acscd.hpp>
#include <eve/function/asec.hpp>
#include <eve/function/asecd.hpp>
#include <eve/function/asin.hpp>
#include <eve/function/asind.hpp>
#include <eve/function/atan.hpp>
#include <eve/function/atan2.hpp>
#include <eve/function/atan2d.hpp>
#include <eve/function/atand.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(inverse_trigo_, inverse_trigo);
}

#include <eve/function/radindeg.hpp>

