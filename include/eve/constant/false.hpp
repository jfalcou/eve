//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_FALSE_HPP_INCLUDED
#define EVE_CONSTANT_FALSE_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/as.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(false_, false_);

  template<typename T>
  EVE_FORCEINLINE auto False(as_<T> const & = {}) noexcept
  {
    return as_logical_t<T>(false);
  }

  EVE_MAKE_NAMED_CONSTANT(false_, False);
}

#endif
