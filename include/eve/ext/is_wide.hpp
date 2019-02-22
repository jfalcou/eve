//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_EXT_IS_WIDE_HPP_INCLUDED
#define EVE_EXT_IS_WIDE_HPP_INCLUDED

#include <type_traits>
#include <eve/forward.hpp>

namespace eve::ext
{
  template<typename Type>
  struct is_wide : std::false_type
  {
  };

  template<typename Type>
  struct is_wide<Type &> : is_wide<Type>
  {
  };

  template<typename Type>
  struct is_wide<Type const> : is_wide<Type>
  {
  };

  template<typename Type>
  struct is_wide<Type const &> : is_wide<Type>
  {
  };

  template<typename Type>
  struct is_wide<Type &&> : is_wide<Type>
  {
  };

  template<typename Type, typename Size, typename ABI>
  struct is_wide<wide<Type, Size, ABI>> : std::true_type
  {
  };

  template<typename Type>
  using is_wide_t = typename is_wide<Type>::type;

  template<typename Type>
  inline constexpr bool is_wide_v = is_wide_t<Type>::value;
}

#endif
