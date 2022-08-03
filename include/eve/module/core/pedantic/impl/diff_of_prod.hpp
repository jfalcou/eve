//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<floating_real_value T
           , floating_real_value U, floating_real_value V, floating_real_value W >
  EVE_FORCEINLINE auto diff_of_prod_(EVE_SUPPORTS(cpu_)
                                  , pedantic_type const &
                                   , const T& a
                                   , const U& b
                                   , const V& c
                                   , const W& d
                                   ) noexcept
  {
    return diff_of_prod(a, b, c, d);
  }

}
