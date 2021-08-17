//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/forward.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  // Element_type : extracts the scalar parts
  //================================================================================================
  template<typename T> struct element_type { using type = T; };

  template<typename T, typename N>             struct element_type<wide<T,N>>   { using type = T; };
  template<typename T>                         struct element_type<wide<T>>     { using type = T; };

  template<typename T>
  struct element_type<logical<T>>     { using type = logical<typename element_type<T>::type>; };

  template<typename T>
  using element_type_t = typename element_type<T>::type;
}
