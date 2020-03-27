//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONCEPT_VALUE_HPP_INCLUDED
#define EVE_CONCEPT_VALUE_HPP_INCLUDED

#include <eve/forward.hpp>
#include <type_traits>
#include <eve/concept/stdconcepts.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/concept/vectorized.hpp>

namespace eve
{
  template<typename T> concept value                          = simd_value<T> || scalar_value<T>; 
  template<typename T> concept integral_value                 = value<T> && std::integral<detail::value_type_t<T>>;
  template<typename T> concept signed_value                   = value<T> && std::signed_type<detail::value_type_t<T>>;
  template<typename T> concept unsigned_value                 = value<T> && std::unsigned_integral<detail::value_type_t<T>>;
  template<typename T> concept signed_integral_value          = value<T> && std::signed_integral<detail::value_type_t<T>>; 
  template<typename T> concept floating_value                 = value<T> && std::floating_point<detail::value_type_t<T>>;
  template<typename T> concept real_value                     = simd_real_value<T> || scalar_real_value<T>; 
  
}

#endif
