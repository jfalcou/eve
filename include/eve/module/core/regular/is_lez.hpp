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
  //!   @var is_lez
  //!   @brief Returns a logical true  if and only if the element value is less or equal to 0.
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
  //!      eve::as_logical<T> is_lez(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [argument](@ref eve::value).
  //!
  //!   **Return value**
  //!
  //!    The truth value of
  //!    is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!    Returns [elementwise](@ref glossary_elementwise) `x <=  0`.
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve;::is_lez[mask](x)` provides a masked version of `eve::is_lez` which is
  //!     equivalent to `if_else (mask, is_lez(x), eve::false( eve::as(x)))`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/is_lez.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(is_lez_, is_lez);
}

#include <eve/module/core/regular/impl/is_lez.hpp>
