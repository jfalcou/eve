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
  //! @addtogroup core_arithmetic
  //! @{
  //!   @var sub
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
  //!      template< eve::value Ts ...>
  //!      eve::common_compatible_t<Ts, ...> sub(Ts ... xs) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `... xs` :  [arguments](eve::value).
  //!
  //!    **Return value**
  //!
  //!    The value of the difference  of the the first argument with the sum of fall other
  //!    is returned.
  //!
  //!   **Note**
  //!
  //!     Take care that for floating entries, this operation  is only 'almost' associative.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/sub.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::sub[mask](x, ...)` provides a masked
  //!     version of `sub` which is
  //!     equivalent to `if_else(mask, sub(x, ...), x)`
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/sub.cpp}
  //!
  //!   * eve::saturated
  //!
  //!     The call `eve::saturated(eve::sub)(...)` computes
  //!     a saturated version of `eve::sub`.
  //!
  //!     Take care that for signed integral
  //!     entries this kind ofoperation  is highly order dep�nding. We do not recommand
  //!     to use it for more than 2 parameters.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/saturated/sub.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sub_, sub);
}

#include <eve/module/core/regular/impl/sub.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/sub.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/sub.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/sub.hpp>
#endif
