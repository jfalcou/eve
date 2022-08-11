//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/if_else.hpp>

namespace eve
{
EVE_MAKE_CALLABLE(replace_ignored_, replace_ignored);

namespace detail
{
  //================================================================================================
  // Helper function - Replace ignored value with an alternative
  //================================================================================================
  template<simd_value Wide, conditional_expr Ignore, typename Other>
  EVE_FORCEINLINE auto
  replace_ignored_(EVE_SUPPORTS(cpu_), Wide x, Ignore ignore, Other with) noexcept
      -> decltype(eve::if_else[ignore](x, with))
  {
    return eve::if_else[ignore](x, with);
  }
}
}
