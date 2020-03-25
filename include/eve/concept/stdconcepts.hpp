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

#include <eve/forward.hpp>
#include <type_traits>

namespace std
{

  template<typename T> concept floating_point          = std::is_floating_point_v<T>;
  template<typename T> concept integral                = std::is_integral_v<T>;
  template<typename T> concept signed_type             = std::is_signed_v<T>;
  template<typename T> concept unsigned_integral       = std::is_unsigned_v<T>;
  template<typename T> concept signed_integral         = std::is_signed_v<T> && std::is_integral_v<T>;
  template<typename T, typename U> concept same_as     = std::is_same_v<T, U> && std::is_same_v<U, T>;  
  
}

#endif
