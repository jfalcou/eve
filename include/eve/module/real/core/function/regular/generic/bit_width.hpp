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
#include <eve/detail/implementation.hpp>
#include <eve/function/countl_zero.hpp>

#include <bit>

namespace eve::detail
{
  template<unsigned_value T> EVE_FORCEINLINE T bit_width_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    using elt_t = element_type_t<T>;
    return T(sizeof(elt_t) * 8 - countl_zero(v));
  }

}

