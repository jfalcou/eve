//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2021 Joel FALCOU
  Copyright 2021 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/if_else.hpp>

#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(replace_ignored_, replace_ignored);

  namespace detail
  {
    //================================================================================================
    // Helper function - Replace ignored value with an alternative
    //================================================================================================
    template <simd_value Wide, conditional_expr Ignore, value Other>
    EVE_FORCEINLINE Wide replace_ignored_ ( EVE_SUPPORTS(cpu_)
                                          , Wide x, Ignore ignore, Other with
                                            ) noexcept
    {
      return eve::if_else[ignore](x, with);
    }
  }
}
