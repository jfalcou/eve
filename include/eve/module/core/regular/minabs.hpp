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
  //!   @var minabs
  //!   @brief Computes the  minimum  of the absolute value of its [arguments](@ref eve::value).
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
  //!      template< eve::value T, eve::value Ts ... >
  //!      eve::common_compatible_t<T, Ts...> minabs(T x, Ts ... xs) noexcept;
  //!
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `xs...` :  [arguments](@ref eve::value).
  //!
  //!    **Return value**
  //!
  //!    The value of the minimum of the absolute value of the arguments is returned.
  //!
  //!   **Notes**
  //!
  //!     * If any element of the inputs is a `Nan`, the corresponding output element
  //!       is system-dependent.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/minabs.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::minabs[mask](x, ...)` provides a masked
  //!     version of `minabs` which is
  //!     equivalent to `if_else(mask, minabs(x, ...), x)`
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/minabs.cpp}
  //!
  //!   * eve::pedantic, eve::numeric
  //!
  //!     * The call `pedantic(minabs)(x,args,...)`  ensures the conformity
  //!       to the standard behaviour, that is
  //!       for two parameters  (on an  [elementwise](@ref glossary_elementwise) basis)
  //!       to be semanticaly equivalent to:
  //!       `(|x| < |y|) ? |x| : |y|` and this behaviour is also ensured on n parameters calls
  //!       as if this scheme was recursively used.
  //!
  //!     *  The call `numeric(minabs)(x,args,...)`  ensures that  if any element of the
  //!        inputs is not a `Nan`, the corresponding
  //!        output element will not be a `Nan`.
  //!
  //!     **Example**
  //!
  //!        @godbolt{doc/core/pedantic/minabs.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(minabs_, minabs);
}

#include <eve/module/core/regular/impl/minabs.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/minabs.hpp>
#endif
