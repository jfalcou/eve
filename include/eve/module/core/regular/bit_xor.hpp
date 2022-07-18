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
  //!   @var bit_xor
  //!   @brief Computes the bitwise XOR of its arguments.
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
  //!      T bit_xor(T x, Ts... xs) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`:       first argument.
  //!     * `xs...` :  other arguments.
  //!
  //!    **Return value**
  //!
  //!      The value of the bitwise XOR of its arguments in the type of the first one
  //!      is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/bit_xor.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::bit_xor[mask](x, ...)` provides a masked
  //!     version of `bit_xor` which is
  //!     equivalent to `if_else(mask, bit_xor(x, ...), x)`
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/bit_xor.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(bit_xor_, bit_xor);
}

#include <eve/module/core/regular/impl/bit_xor.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/bit_xor.hpp>
#endif
