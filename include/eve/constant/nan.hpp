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

#include <eve/concept/value.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/as.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(nan_, nan_);

  template<floating_value T>
  EVE_FORCEINLINE auto Nan(as_<T> const & = {}) noexcept
  {
    return Allbits<T>();
  }

  EVE_MAKE_NAMED_CONSTANT(nan_, Nan);
}

