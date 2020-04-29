//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_HAS_SINGLE_BIT_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_HAS_SINGLE_BIT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/is_pow2.hpp>

namespace eve
{
  inline auto const has_single_bit = eve::is_pow2;
}

#endif
