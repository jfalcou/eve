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
  //!   @var floor
  //!   @brief Computes the largest integer not greater than the input.
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
  //!      template< eve::real_value T >
  //!      T floor(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!    **Return value**
  //!
  //!    The largest integer not greater than `x`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/floor.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve;::floor[mask](x)` provides a masked version of `eve::floor` which is
  //!     equivalent to `if_else (mask, floor(x), x)`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/floor.cpp}
  //!
  //!   * eve::tolerant
  //!
  //!     The expression `tolerant(floor)(x, tol)` computes a tolerant floor value for `x`,
  //!     where `x` must be a floating value.
  //!
  //!      * If `tol` is a floating value computes the floor with
  //!        a tolerance `tol` using Hagerty's FL5 function.
  //!      * If `tol` is an integral value n compute the floor of
  //!        the next nth representable value in the `x` type.
  //!      * If `tol` is omitted the tolerance is taken to 3 times
  //!        the machine \f$\epsilon\f$ in the `x` type (`3*eps(as(x))`).
  //!
  //!      @godbolt{doc/core//fuzzy/floor.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(floor_, floor);
}

#include <eve/module/core/regular/impl/floor.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/floor.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/floor.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/floor.hpp>
#endif
