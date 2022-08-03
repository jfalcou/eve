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
  //!   @var max
  //!   @brief Computes the  maximum  of its [arguments](@ref eve::value).
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
  //!      eve::common_compatible_t<T, Ts...> max(T x, Ts ... xs) noexcept;
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
  //!    The value of the maximum  of the arguments is returned.
  //!
  //!   **Notes**
  //!
  //!     * If any element of the inputs is a `Nan`, the corresponding output element
  //!       is system-dependent.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/max.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::max[mask](x, ...)` provides a masked
  //!     version of `max` which is
  //!     equivalent to `if_else(mask, max(x, ...), x)`
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/max.cpp}
  //!
  //!   * eve::pedantic, eve::numeric
  //!
  //!     * The call `pedantic(max)(x,args,...)`  ensures the conformity
  //!       to the standard behaviour, that is
  //!       for two parameters  (on an  [elementwise](@ref glossary_elementwise) basis)
  //!       to be semantically equivalent to:
  //!       `(x < y) ? y : x` and this behaviour is also ensured on n parameters calls
  //!       as if this scheme was recursively used.
  //!
  //!     *  The call `numeric(max)(x,args,...)`  ensures that  if any element of the
  //!        inputs is not a `Nan`, the corresponding
  //!        output element will not be a `Nan`.
  //!
  //!     **Example**
  //!
  //!        @godbolt{doc/core/pedantic/max.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(max_, max);
}

#include <eve/module/core/regular/impl/max.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/max.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/max.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/max.hpp>
#endif
