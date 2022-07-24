/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_predicates
  //! @{
  //!   @var is_denormal
  //!   @brief Returns a logical true if and only if the element value is denormal.
  //!
  //!   $details$
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::value T >
  //!      eve::as_logical<T> is_denormal(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!   **Return value**
  //!
  //!     The call `is_denormal(x)` is semantically  equivalent to:
  //!
  //!     @code
  //!       if   constexpr(floating_value<T>) return (abs(x) < Smallestposval(as(x))) && is_nez(x);
  //!       else constexpr(integral_value<T>) return false_(as(x));
  //!    @endcode
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/is_denormal.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(is_denormal_, is_denormal);
}

#include <eve/module/core/regular/impl/is_denormal.hpp>
