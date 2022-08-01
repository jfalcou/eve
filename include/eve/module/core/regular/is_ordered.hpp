//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/arch.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_predicates
  //! @{
  //!   @var is_ordered
  //!   @brief Returns a logical true  if and only no parameter is NaN.
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
  //!      template< eve::value T, eve::value U >
  //!      eve::as_logical<T> is_ordered(T x,U y) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y` :  [argument](@ref eve::value).
  //!
  //!   **Return value**
  //!
  //!    The call `eve::is_ordered(x,y)`  is semantically  equivalent
  //!    to `eve::is_not_nan(x) && eve::is_not_nan(y)`:
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/is_ordered.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve;::is_ordered[mask](x,y)` provides a masked version of `eve::is_ordered` which is
  //!     equivalent to `if_else (mask, is_ordered(x), eve::false( eve::as(x,y)))`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/is_ordered.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(is_ordered_, is_ordered);
}

#include <eve/module/core/regular/impl/is_ordered.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_ordered.hpp>
#endif
