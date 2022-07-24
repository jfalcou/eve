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
  //! @addtogroup core_fma_family
  //! @{
  //!   @var fam
  //!   @brief Computes the fused add multiply of its three parameters.
  //!
  //!   The call `fam(x, y, z)` is similar to `x+y*z` as if calculated to infinite precision
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
  //!      eve::compatible_value_t fam(T x, U y,  V z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y`, `z` :  arguments.
  //!
  //!    **Return value**
  //!
  //!    The value of `x+y*z` as if calculated to infinite precision
  //!    and rounded once is returned,  but only if the hardware is in capacity
  //!    to do it at reasonnable cost.
  //!
  //!    **Note**
  //!
  //!       This `fam` implementation provides those properties for all
  //!       [integral real value](@ref eve::integral_value)
  //!       and when possible for [floating real value](@ref eve::floating_value).
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/fam.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::fam[mask](x, ...)` provides a masked
  //!     version of `fam` which is
  //!     equivalent to `if_else(mask, fam(x, ...), x)`
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/fam.cpp}
  //!
  //!   * eve::pedantic, eve::numeric
  //!
  //!       * The call `pedantic(fam)(x,y,z)` ensures the one rounding property.
  //!       This can be very expensive if the system has no hardware capability.
  //!
  //!       * The call `numeric(fam)(x,y,z)` ensures the full compliance to fam properties.
  //!        This can be very expensive if the system has no hardware capability.
  //!
  //!       * see the above regular example.
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(fam_, fam);
}

#include <eve/arch.hpp>
#include <eve/module/core/regular/impl/fam.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fam.hpp>
#endif
