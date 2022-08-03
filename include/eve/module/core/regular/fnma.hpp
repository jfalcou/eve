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
  //! @addtogroup core_fma_family
  //! @{
  //!   @var fnma
  //!   @brief Computes the fused negate multiply add of its three parameters.
  //!
  //!   The call `fnma(x, y, z)` is similar to `-x*y+z` as if calculated to infinite precision
  //!   and rounded once to fit the result as much as supported by the hardware.
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
  //!      eve::compatible_value_t fnma(T x, U y,  V z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y`, `z` :  [arguments](@ref eve::value).
  //!
  //!    **Return value**
  //!
  //!    The value of `-x*y+z` as if calculated to infinite precision
  //!    and rounded once is returned,  but only if the hardware is in capacity
  //!    to do it at reasonnable cost.
  //!
  //!    **Note**
  //!
  //!       This `fnma` implementation provides those properties for all
  //!       [integral real value](@ref eve::integral_value)
  //!       and when possible for [floating real value](@ref eve::floating_value).
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/fnma.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::fnma[mask](x, ...)` provides a masked
  //!     version of `fnma` which is
  //!     equivalent to `if_else(mask, fnma(x, ...), x)`
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/fnma.cpp}
  //!
  //!   * eve::pedantic, eve::numeric
  //!
  //!       * The call `pedantic(fnma)(x,y,z)` ensures the one rounding property.
  //!       This can be very expensive if the system has no hardware capability.
  //!
  //!       * The call `numeric(fnma)(x,y,z)` ensures the full compliance to fnma properties.
  //!        This can be very expensive if the system has no hardware capability.
  //!
  //!       * see the above regular example.
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(fnma_, fnma);
}

#include <eve/module/core/regular/impl/fnma.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fnma.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/fnma.hpp>
#endif
