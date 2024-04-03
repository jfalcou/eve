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

//================================================================================================
//! @addtogroup core_logical
//! @{
//!    @var replace_ignored
//!    @brief A small helper tto replace ignored values
//!
//!   **Defined in Header**
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   A convinience wrapper around if_else.
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::value T, eve::conditional_expr Ignore, eve::value Other >
//!      auto replace_ignored(T x, Ignore ignore, Other with )
//!        -> decltype(eve::if_else[ignore](x, with))
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   * `x` - main value
//!   * `ignore` - selection
//!   * `with` - value to replace with
//!
//!   **Return value**
//!
//!   Same as if_else.
//!
//================================================================================================

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
