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
  //! @addtogroup core_arithmetic
  //! @{
  //!   @var add
  //!   @brief Computes the sum of its arguments.
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
  //!      template< eve::value T ... >
  //!      eve::common_compatible_t<T, ...> add(T ... x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x...` :  [arguments](eve::value).
  //!
  //!    **Return value**
  //!
  //!    The value of the sum of the arguments is returned.
  //!
  //!   **Note**
  //!
  //!     Take care that for floating entries, the addition is only 'almost' associative.
  //!     This call perform additions in reverse incoming order.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/add.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::add[mask](x, ...)` provides a masked
  //!     version of `add` which is
  //!     equivalent to `if_else(mask, add(x, ...), x)`
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/add.cpp}
  //!
  //!   * eve::saturated
  //!
  //!     The call `eve::saturated(eve::add)(...)` computes
  //!     a saturated version of `eve::add`.
  //!
  //!     Take care that for signed integral
  //!     entries this kind of addition is not associative at all.
  //!     This call perform saturated additions in reverse incoming order.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/saturated/add.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(add_, add);
}

#include <eve/module/core/regular/impl/add.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/add.hpp>
#endif
