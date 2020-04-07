//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CARDINAL_HPP_INCLUDED
#define EVE_CARDINAL_HPP_INCLUDED

#include <eve/concept/rebindable.hpp>
#include <eve/detail/is_wide.hpp>
#include <eve/forward.hpp>
#include <cstddef>

namespace eve
{
  template<std::ptrdiff_t Cardinal> struct fixed;
  struct  scalar_cardinal;

  template<typename Type>
  struct cardinal : scalar_cardinal
  {
    using type = scalar_cardinal;
  };

  template<typename Type, typename Size, typename ABI>
  struct cardinal<wide<Type, Size, ABI>> : Size
  {
     using type = Size;
  };

  template<typename Type>
  struct cardinal<logical<Type>> : cardinal<Type>
  {
  };

  template<typename Type>
  requires( rebindable<Type> )
  struct cardinal<Type> : cardinal<std::tuple_element_t<0,Type>>
  {
  };

  template<typename Type>
  using cardinal_t = typename cardinal<Type>::type;

  template<typename Type>
  inline constexpr auto cardinal_v = cardinal<Type>::value;
}

#endif
