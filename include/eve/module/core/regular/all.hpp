//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core
  //! @{
  //!   @var all
  //!   @brief Computes the
  //!
  //!   $details$
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
  //!      template< eve::logical_value T >
  //!      bool all(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument(@ref eve::logical_value).
  //!
  //!    **Return value**
  //!
  //!    A bool value which is true if and only if all elements of `x` are true_
  //!    is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/all.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::all[mask](x)` provides a masked
  //!     version of `all` which is
  //!     equivalent to : all not masked elements are true.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/all.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(all_, all);
}

#include <eve/module/core/regular/impl/all.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/all.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/all.hpp>
#endif
