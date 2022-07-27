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
  //!   @var bit_notor
  //!   @brief Computes the bitwise NOTOR of its [arguments](@ref eve::value).
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
  //!      T bit_notor(T x, Ts... xs) noexcept;
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
  //!     * For two parameters it computes the  bitwise NOTOR of the two parameters
  //!     * For more than two parameters the call is  semantically equivalent to to `bit_notor(a0, bit_or(xs...))`
  //!     *  The value returned is in the type of the first parameter
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/bit_notor.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::bit_notor[mask](x, ...)` provides a masked
  //!     version of `bit_notor` which is
  //!     equivalent to `if_else(mask, bit_notor(x, ...), x)`
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/bit_notor.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(bit_notor_, bit_notor);
}

#include <eve/module/core/regular/impl/bit_notor.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/bit_notor.hpp>
#endif
