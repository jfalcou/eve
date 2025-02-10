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
    template<simd_value T, relative_conditional_expr Ignore, value Other>
    constexpr EVE_FORCEINLINE T operator()(T x, Ignore ignore, Other with) const noexcept
    {
      return eve::if_else(ignore, x, with);
    }

    template<simd_value T, relative_conditional_expr Ignore, generator Other>
    constexpr EVE_FORCEINLINE T operator()(T x, Ignore ignore, Other with) const noexcept
    {
      return eve::if_else(ignore, x, with);
    }
  };

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
  //!      template<simd_value T, relative_conditional_expr Ignore, value Other>
  //!      T replace_ignored(T x, Ignore ignore, Other with);
  //!
  //!      template<simd_value T, relative_conditional_expr Ignore, generator Other>
  //!      T replace_ignored(T x, Ignore ignore, Other with);
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
