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

#include <eve/detail/implementation.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/as.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(true_, true_);

  template<typename T>
  EVE_FORCEINLINE auto True(eve::as_<T> const & = {}) noexcept
  {
    return as_logical_t<T>(true);
  }

  EVE_MAKE_NAMED_CONSTANT(true_, True);
}

