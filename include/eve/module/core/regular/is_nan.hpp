//==================================================================================================
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
  //!   @var is_nan
  //!   @brief Returns a logical true  if and only if the element value is NaN
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
  //!      eve::as_logical<T> is_nan(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [argument](@ref eve::value).
  //!
  //!   **Return value**
  //!
  //!       The call `eve::is_nan(x)`  is semantically  equivalent to:
  //!
  //!       @code
  //!         if   constexpr(floating_value<T>) return is_not_equal(x, x);
  //!         else constexpr(integral_value<T>) return false_(as(x));
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/is_nan.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve;::is_nan[mask](x)` provides a masked version of `eve::is_nan` which is
  //!     equivalent to `if_else (mask, is_nan(x), eve::false( eve::as(x)))`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/is_nan.cpp}
  //!
  //! @}
  //================================================================================================
 EVE_MAKE_CALLABLE(is_nan_, is_nan);
}

#include <eve/module/core/regular/impl/is_nan.hpp>
