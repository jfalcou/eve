//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

namespace eve
{
  template<typename T> concept tagged_callable_object = requires(T a)
  {
    typename T::tag_type;
  };
}
