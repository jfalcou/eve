//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

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

  template<typename Type, typename Size>
  struct cardinal<wide<Type, Size>> : Size
  {
     using type = Size;
  };

  template<typename Type>
  struct cardinal<logical<Type>> : cardinal<Type>
  {
  };

  template<typename Type>
  using cardinal_t = typename cardinal<Type>::type;

  template<typename Type>
  inline constexpr auto cardinal_v = cardinal<Type>::value;
}
