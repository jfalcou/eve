//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018-2021 Joel FALCOU
  Copyright 2018-2021 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
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
