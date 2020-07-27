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
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(mone_, mone_);

  template<typename T>
  EVE_FORCEINLINE auto Mone(as_<T> const & = {}) noexcept
  {
    return T(-1);
  }

  EVE_MAKE_NAMED_CONSTANT(mone_, Mone);
}

