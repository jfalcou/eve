//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONCEPT_STDCONCEPTS_HPP_INCLUDED
#define EVE_CONCEPT_STDCONCEPTS_HPP_INCLUDED

#include <type_traits>
#include <functional>
#include <concepts>

namespace eve
{
  template<typename T> concept arithmetic = std::is_arithmetic_v<T>;
}

#endif
