//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_EXT_AS_WIDE_HPP_INCLUDED
#define EVE_EXT_AS_WIDE_HPP_INCLUDED

#include <eve/forward.hpp>

namespace eve
{
  template<typename Type, typename Size, typename EnableIf = void>
  struct as_wide
  {
    using type = eve::wide<Type, Size>;
  };

  template<typename Type, typename Size>
  struct as_wide<logical<Type>, Size>
  {
    using type = logical<typename as_wide<Type, Size>::type>;
  };

  template<typename Type, typename N, typename Size>
  struct as_wide<wide<Type,N>,Size>
  {
    using type = wide<Type, Size>;
  };

  template<typename Type, typename Size>
  using as_wide_t = typename as_wide<Type, Size>::type;
}

#endif
