//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/forward.hpp>

namespace eve
{
  //================================================================================================
  // Concept for conditional expression
  //================================================================================================
  template<typename T> concept conditional_expr = requires(T a)
  {
    { T::has_alternative  };
    { T::is_inverted      };
    { T::is_complete      };
    { a.mask(eve::as_<eve::wide<int>>())  };
  };

  template<typename T> concept relative_conditional_expr = conditional_expr<T> && requires(T a)
  {
    { a.bitmap(eve::as_<eve::wide<int>>()) };
    { a.count(eve::as_<eve::wide<int>>())  };
    { a.offset(eve::as_<eve::wide<int>>()) };
    { a.roffset(eve::as_<eve::wide<int>>()) };
  };

  template <typename T> concept attribute_conditional = requires (T)
  {
    { typename T::modifier_conditional{} };
  };
}
