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
  //! @addtogroup core_bitops
  //! @{
  //!   @var bit_notand
  //!   @brief Computes the bitwise NOTAND of its [arguments](@ref eve::value).
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
  //!      template< eve::value T, eve::value Ts... >
  //!      T bit_notand(T x, Ts... xs) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`:       first [argument](@ref eve::value).
  //!     * `xs...` :  other [arguments](@ref eve::value).
  //!
  //!    **Return value**
  //!
  //!     * For two parameters it computes the  bitwise NOTAND of the two parameters
  //!     * For more than two parameters the call is  semantically equivalent to to `bit_notand(a0, bit_and(xs...))`
  //!     *  The value returned is in the type of the first parameter
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/bit_notand.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::bit_notand[mask](x, ...)` provides a masked
  //!     version of `bit_notand` which is
  //!     equivalent to `if_else(mask, bit_notand(x, ...), x)`
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/bit_notand.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(bit_notand_, bit_notand);
}

#include <eve/module/core/regular/impl/bit_notand.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/bit_notand.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/bit_notand.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/bit_notand.hpp>
#endif
