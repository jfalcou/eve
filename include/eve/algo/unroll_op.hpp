//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/eve.hpp>

namespace eve::algo
{
  template<std::ptrdiff_t how_much, typename Op> EVE_FORCEINLINE auto unroll_op(Op op)
  {
    return [&]<std::ptrdiff_t... idxs>(std::integer_sequence<std::ptrdiff_t, idxs...>)
    {
      return (op(eve::index<idxs>) || ...);
    }
    (std::make_integer_sequence<std::ptrdiff_t, how_much> {});
  }

}
