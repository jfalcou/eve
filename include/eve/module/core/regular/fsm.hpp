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
  //!   @var fsm
  //!   @brief Computes the fused negate add  multiply of its three parameters.
  //!
  //!   The call `fsm(x, y, z)` is similar to `-x+y*z` as if calculated to infinite precision
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
  //!      eve::compatible_value_t fsm(T x, U y,  V z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y`, `z` :  [arguments](@ref eve::value).
  //!
  //!    **Return value**
  //!
  //!    The value of `-x+y*z` as if calculated to infinite precision
  //!    and rounded once is returned,  but only if the hardware is in capacity
  //!    to do it at reasonnable cost.
  //!
  //!    **Note**
  //!
  //!       This `fsm` implementation provides those properties for all
  //!       [integral real value](@ref eve::integral_value)
  //!       and when possible for [floating real value](@ref eve::floating_value).
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/fsm.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::fsm[mask](x, ...)` provides a masked
  //!     version of `fsm` which is
  //!     equivalent to `if_else(mask, fsm(x, ...), x)`
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/fsm.cpp}
  //!
  //!   * eve::pedantic, eve::numeric
  //!
  //!       * The call `pedantic(fsm)(x,y,z)` ensures the one rounding property.
  //!       This can be very expensive if the system has no hardware capability.
  //!
  //!       * The call `numeric(fsm)(x,y,z)` ensures the full compliance to fsm properties.
  //!        This can be very expensive if the system has no hardware capability.
  //!
  //!       * see the above regular example.
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(fsm_, fsm);
}

#include <eve/module/core/regular/impl/fsm.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fsm.hpp>
#endif
