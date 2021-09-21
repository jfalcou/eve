//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
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
  };

  template<typename T> concept relative_conditional_expr = conditional_expr<T> && requires(T a)
  {
    { a.count(eve::as<eve::wide<int>>())  };
    { a.offset(eve::as<eve::wide<int>>()) };
    { a.roffset(eve::as<eve::wide<int>>()) };
  };
}
