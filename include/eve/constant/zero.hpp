//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_ZERO_HPP_INCLUDED
#define EVE_CONSTANT_ZERO_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(zero_, zero_);

  template<typename T>
  EVE_FORCEINLINE auto Zero(as_<T> const & = {})
  {
    return T(0);
  }

  EVE_MAKE_NAMED_CONSTANT(zero_, Zero);
}

#endif
