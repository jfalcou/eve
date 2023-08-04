//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<ordered_value V1, ordered_value V2>
  EVE_FORCEINLINE auto dot_( EVE_SUPPORTS(cpu_), V1 const& v1, V2 const & v2) noexcept
  {
    return v1*v2;
  }
}
