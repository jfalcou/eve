//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_TRUE_HPP_INCLUDED
#define EVE_CONSTANT_TRUE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as_logical.hpp>
#include <eve/is_logical.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(true_, true_);

  template<typename T>
  EVE_FORCEINLINE auto True(as_<T> const & = {})
  {
    return as_logical_t<T>(true);
  }


  EVE_MAKE_NAMED_CONSTANT(true_, True);
}

#endif
