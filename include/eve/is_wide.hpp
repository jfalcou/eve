//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_IS_WIDE_HPP_INCLUDED
#define EVE_IS_WIDE_HPP_INCLUDED

#include <eve/ext/is_wide.hpp>

namespace eve
{
  template<typename T>
  struct is_wide : ext::is_wide<T>
  {
  };

  template<typename Type>
  using is_wide_t = typename is_wide<Type>::type;

  template<typename Type>
  inline constexpr bool is_wide_v = is_wide_t<Type>::value;

  template<typename T>
  using Wide = std::enable_if_t<is_wide_v<T>>;

  template<typename T>
  using Scalar = std::enable_if_t<!is_wide_v<T>>;
}

#endif
