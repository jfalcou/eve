//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve
{
  //================================================================================================
  // Concept for swizzling pattern
  //================================================================================================
  template<typename T> concept shuffle_pattern = requires(T p)
  {
    { T::size()       };
    { T::has_zeros()  };
    { T::validate(0)  };
  };
}
