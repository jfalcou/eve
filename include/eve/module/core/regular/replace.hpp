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
  template<typename Options>
  struct replace_ignored_t : callable<replace_ignored_t, Options>
  {
    template<simd_value Wide, conditional_expr Ignore, typename Other>
    constexpr EVE_FORCEINLINE Wide operator()(Wide x, Ignore ignore, Other with) const noexcept
    {
      return eve::if_else(ignore, x, with);
    }
  };

  // TODO DOC is it to be in user interface ?
  //================================================================================================
  //! @addtogroup core_logical
  //! @{
  //!    @var replace_ignored
  //!    @brief A small helper to replace ignored values
  //!
  //!   @groupheader{Header file}
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
  //!        -> decltype(eve::if_else(ignore, x, with))
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
  inline constexpr auto replace_ignored = functor<replace_ignored_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}
