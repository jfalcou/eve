//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_BINARIZE_NOT_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_BINARIZE_NOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>
#include <eve/constant/mone.hpp>
#include <eve/constant/allbits.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(binarize_not_, binarize_not);
}

#endif
 
